disk init name = "CLDAT", 
        physname = "SYS:\SYBASE\CLDAT.DAT", vdevno = 4,size = 50000
disk init name = "CLLOG", 
        physname = "SYS:\SYBASE\CLLOG.DAT", vdevno = 5,size = 10000
create database CLINICUM on CLDAT = 50000 log ON CLLOG = 10000
use CLINICUM
CREATE PROCEDURE CLTABLES AS
  SELECT name from sysobjects WHERE type = 'U'
CREATE PROCEDURE CLCOLS @tn char(64) AS
  SELECT name,type from syscolumns 
    WHERE id = (SELECT id from sysobjects WHERE name = @tn)
USE master
sp_dboption CLINICUM, 'allow nulls by default', true
USE CLINICUM
CHECKPOINT

