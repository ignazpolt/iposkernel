param(
    [Parameter(Position=0)]
    [string]$SourcePattern,

    [Parameter(Position=1)]
    [string]$OutputPattern,

    [Parameter(Position=2)]
    [string]$Profile
)

$ErrorActionPreference = "Continue"
if (Get-Variable -Name PSNativeCommandUseErrorActionPreference -ErrorAction SilentlyContinue) {
    $PSNativeCommandUseErrorActionPreference = $false
}

function Write-ErrLog {
    param([string]$Message)
    $errPath = Join-Path (Get-Location) "err"
    Add-Content -Path $errPath -Value $Message
}

function Resolve-Sources {
    param([string]$Pattern)

    if ([string]::IsNullOrWhiteSpace($Pattern)) {
        throw "Missing source pattern"
    }

    $leaf = Split-Path -Path $Pattern -Leaf
    $patternBase = [System.IO.Path]::GetFileNameWithoutExtension($leaf)
    $patternExt = [System.IO.Path]::GetExtension($leaf)

    $items = Get-ChildItem -Path $Pattern -File -ErrorAction SilentlyContinue
    if ($items) {
        return $items
    }

    if (Test-Path -LiteralPath $Pattern -PathType Leaf) {
        return ,(Get-Item -LiteralPath $Pattern)
    }

    if ($Pattern -match '\.cpp$') {
        $altPattern = [System.Text.RegularExpressions.Regex]::Replace($Pattern, '\.cpp$', '.cpx', 'IgnoreCase')
        $items = Get-ChildItem -Path $altPattern -File -ErrorAction SilentlyContinue
        if ($items) {
            return $items
        }

        if (Test-Path -LiteralPath $altPattern -PathType Leaf) {
            return ,(Get-Item -LiteralPath $altPattern)
        }
    }

    if (-not ($Pattern.Contains("\") -or $Pattern.Contains("/"))) {
        $candidates = Get-ChildItem -Path $sourceRoot -Recurse -File -ErrorAction SilentlyContinue |
            Where-Object { [System.IO.Path]::GetFileNameWithoutExtension($_.Name).Equals($patternBase, [System.StringComparison]::OrdinalIgnoreCase) }

        if ($candidates) {
            if ([string]::IsNullOrWhiteSpace($patternExt)) {
                return $candidates
            }

            $preferred = $candidates | Where-Object { $_.Extension.Equals($patternExt, [System.StringComparison]::OrdinalIgnoreCase) }
            if ($preferred) {
                return $preferred
            }

            if ($patternExt.Equals('.cpp', [System.StringComparison]::OrdinalIgnoreCase)) {
                $cpx = $candidates | Where-Object { $_.Extension.Equals('.cpx', [System.StringComparison]::OrdinalIgnoreCase) }
                if ($cpx) {
                    return $cpx
                }
            }

            return $candidates
        }
    }

    return @()
}

function Get-OutputFile {
    param(
        [System.IO.FileInfo]$Source,
        [string]$OutPattern,
        [int]$SourceCount
    )

    if ([string]::IsNullOrWhiteSpace($OutPattern)) {
        throw "Missing output pattern"
    }

    $hasWildcard = $OutPattern.Contains("*")

    if (-not $hasWildcard -and $SourceCount -eq 1) {
        return [System.IO.Path]::GetFullPath($OutPattern)
    }

    $outDir = Split-Path -Path $OutPattern -Parent
    if ([string]::IsNullOrWhiteSpace($outDir)) {
        $outDir = "."
    }

    if (-not (Test-Path -LiteralPath $outDir)) {
        New-Item -ItemType Directory -Path $outDir -Force | Out-Null
    }

    $outLeaf = Split-Path -Path $OutPattern -Leaf
    $outExt = [System.IO.Path]::GetExtension($outLeaf)
    if ([string]::IsNullOrWhiteSpace($outExt)) {
        $outExt = $Source.Extension
    }

    $outName = [System.IO.Path]::GetFileNameWithoutExtension($Source.Name) + $outExt
    return [System.IO.Path]::GetFullPath((Join-Path $outDir $outName))
}

function Invoke-Tool {
    param(
        [string]$Exe,
        [string[]]$ToolArgs
    )

    $cmd = "$Exe " + ($ToolArgs -join " ")
    Write-Host $cmd

    $toolOutput = & $Exe @ToolArgs 2>&1
    foreach ($line in $toolOutput) {
        Write-Host $line
    }
    return $LASTEXITCODE
}

if ([string]::IsNullOrWhiteSpace($Profile)) {
    $Profile = "DEFAULT"
}

$repoRoot = [System.IO.Path]::GetFullPath((Join-Path $PSScriptRoot ".."))
function Resolve-SourceRoot {
    param([string]$Root)

    $actVers = $env:ACTVERS
    $candidates = @()

    if (-not [string]::IsNullOrWhiteSpace($actVers)) {
        $candidates += (Join-Path $Root "$actVers\$actVers.SRC")
        $candidates += (Join-Path $Root "$actVers.SRC")
    }

    # Fallback discovery for mixed repository layouts.
    $directSrcDirs = Get-ChildItem -Path $Root -Directory -Filter "*.SRC" -ErrorAction SilentlyContinue
    foreach ($dir in $directSrcDirs) {
        $candidates += $dir.FullName
    }

    $versionDirs = Get-ChildItem -Path $Root -Directory -ErrorAction SilentlyContinue
    foreach ($versionDir in $versionDirs) {
        $nestedSrc = Join-Path $versionDir.FullName ($versionDir.Name + ".SRC")
        if (Test-Path -LiteralPath $nestedSrc -PathType Container) {
            $candidates += $nestedSrc
        }
    }

    foreach ($candidate in $candidates) {
        if (Test-Path -LiteralPath $candidate -PathType Container) {
            return [System.IO.Path]::GetFullPath($candidate)
        }
    }

    return [System.IO.Path]::GetFullPath($Root)
}

$sourceRoot = Resolve-SourceRoot -Root $repoRoot
$includeRoot = Join-Path $sourceRoot "Include"

function Get-ProjectIncludePaths {
    param(
        [string]$SourceRoot,
        [string]$IncludeRoot
    )

    $candidates = @(
        $IncludeRoot,
        $SourceRoot,
        (Join-Path $SourceRoot "Include"),
        (Join-Path (Split-Path -Path $SourceRoot -Parent) "Include")
    )

    $paths = @()
    foreach ($candidate in $candidates) {
        if (-not $candidate) { continue }
        if (Test-Path -LiteralPath $candidate -PathType Container) {
            $paths += $candidate
        }
    }

    return $paths | Select-Object -Unique
}

function Get-JavaIncludePaths {
    $roots = @()

    if ($env:JAVA_HOME) {
        $roots += $env:JAVA_HOME
    }

    $roots += @(
        "$env:ProgramFiles\Java",
        "$env:ProgramFiles(x86)\Java"
    )

    foreach ($r in $roots) {
        if (-not $r) { continue }
        if (-not (Test-Path -LiteralPath $r)) { continue }

        if (Test-Path -LiteralPath (Join-Path $r "include\jni.h")) {
            $base = $r
            $paths = @((Join-Path $base "include"), (Join-Path $base "include\win32"))
            return $paths
        }

        $candidates = Get-ChildItem -Path $r -Directory -ErrorAction SilentlyContinue | Sort-Object Name -Descending
        foreach ($cand in $candidates) {
            $jni = Join-Path $cand.FullName "include\jni.h"
            if (Test-Path -LiteralPath $jni) {
                return @((Join-Path $cand.FullName "include"), (Join-Path $cand.FullName "include\win32"))
            }
        }
    }

    return @()
}

$javaIncludePaths = Get-JavaIncludePaths
$projectIncludePaths = Get-ProjectIncludePaths -SourceRoot $sourceRoot -IncludeRoot $includeRoot

$sources = Resolve-Sources -Pattern $SourcePattern
if ($sources.Count -eq 0) {
    Write-ErrLog "makec: no files matched '$SourcePattern'"
    Write-Host "makec: no files matched '$SourcePattern'"
    exit 1
}

# If sources resolve into a concrete *.SRC tree, prefer that tree for includes.
foreach ($resolvedSource in $sources) {
    $m = [System.Text.RegularExpressions.Regex]::Match(
        $resolvedSource.FullName,
        '^(.*?\.SRC)(\\|/)',
        [System.Text.RegularExpressions.RegexOptions]::IgnoreCase
    )
    if ($m.Success) {
        $sourceRoot = [System.IO.Path]::GetFullPath($m.Groups[1].Value)
        $includeCandidate = Join-Path $sourceRoot "Include"
        if (Test-Path -LiteralPath $includeCandidate -PathType Container) {
            $includeRoot = $includeCandidate
        }
        break
    }
}

$globalFailed = $false

foreach ($src in $sources) {
    $outFile = Get-OutputFile -Source $src -OutPattern $OutputPattern -SourceCount $sources.Count
    $srcExt = $src.Extension.ToLowerInvariant()

    $srcDir = $src.DirectoryName

    if ($srcExt -eq ".rc") {
        $rcArgs = @(
            "/r",
            "/v",
            "/dWIN32",
            "/fo$outFile",
            "/i$srcDir"
        )

        foreach ($projectInclude in $projectIncludePaths) {
            $rcArgs += "/I$projectInclude"
        }

        $rcArgs += $src.FullName

        $rcCode = Invoke-Tool -Exe "rc.exe" -ToolArgs $rcArgs
        if ($rcCode -ne 0) {
            Write-ErrLog "makec RCCOMP failed: $($src.FullName) -> $outFile"
            $globalFailed = $true
        }
        continue
    }

    $commonArgs = @(
        "/nologo",
        "/c",
        "/Zc:forScope-",
        "/DWIN32",
        "/D_WINDOWS",
        "/D_CRT_SECURE_NO_WARNINGS",
        "/I$srcDir"
    )

    foreach ($projectInclude in $projectIncludePaths) {
        $commonArgs += "/I$projectInclude"
    }

    foreach ($jip in $javaIncludePaths) {
        $commonArgs += "/I$jip"
    }

    if ($srcExt -eq ".c") {
        $commonArgs += "/TC"
    } else {
        $commonArgs += "/TP"
        $commonArgs += "/EHsc"
    }

    switch ($Profile.ToUpperInvariant()) {
        "MAKEC1" {
            $commonArgs += @("/W3", "/Zi", "/Od", "/DDEBUG")
        }
        "COMPDLL" {
            $commonArgs += @("/W3", "/Zi", "/Od", "/DDEBUG")
        }
        "COMPDLL1" {
            $commonArgs += @("/W3", "/Zi", "/Od", "/DDEBUG")
        }
        "RCCOMP" {
            # Defensive fallback in case a non-rc source is passed with RCCOMP.
            $commonArgs += @("/W3", "/Zi", "/Od", "/DDEBUG")
        }
        default {
            $commonArgs += @("/W3", "/Zi", "/Od", "/DDEBUG")
        }
    }

    $clArgs = $commonArgs + @("/Fo$outFile", $src.FullName)
    $clCode = Invoke-Tool -Exe "cl.exe" -ToolArgs $clArgs
    if ($clCode -ne 0) {
        Write-ErrLog "makec $Profile failed: $($src.FullName) -> $outFile"
        $globalFailed = $true
    }
}

if ($globalFailed) {
    exit 1
}

exit 0
