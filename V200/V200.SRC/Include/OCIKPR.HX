/*
 * $Header:   P:/marille/clinicum/include/rev/ocikpr.h_v   1.0   31 May 1996 20:18:24   MARTIN  $ 
 */

/* Copyright (c) 1991 by Oracle Corporation */
/*
   NAME
     ocikpr.h - header of K & R compilers
   MODIFIED   (MM/DD/YY)
    rkooi2     11/27/92 -  Changing datatypes (in comments) and return types 
    rkooi2     10/26/92 -  More portability mods 
    rkooi2     10/18/92 -  Changed to agree with oci.c 
    sjain      03/16/92 -  Creation 
*/

/*
 *  Declare the OCI functions.
 *  Prototype information is commented out.
 *  Use this header for non-ANSI C compilers.
 *  Note that you will need to include ocidfn.h in the .c files
 *    to get the definition for cda_def.
 */

#ifndef OCIKPR
#define OCIKPR

#include <oratypes.h>

sword  obndra( /*_ struct cda_def *cursor, text *sqlvar, sword sqlvl,
                 ub1 *progv, sword progvl, sword ftype, sword scale,
                 sb2 *indp, ub2 *alen, ub2 *arcode, ub4 maxsiz,
                 ub4 *cursiz, text *fmt, sword fmtl, sword fmtt _*/ );
sword  obndrn( /*_ struct cda_def *cursor, sword sqlvn, ub1 *progv,
                 sword progvl, sword ftype, sword scale, sb2 *indp,
                 text *fmt, sword fmtl, sword fmtt _*/ );
sword  obndrv( /*_ struct cda_def *cursor, text *sqlvar, sword sqlvl,
                 ub1 *progv, sword progvl, sword ftype, sword scale,
                 sb2 *indp, text *fmt, sword fmtl, sword fmtt _*/ );
sword  obreak( /*_ struct cda_def *lda _*/ );
sword  ocan  ( /*_ struct cda_def *cursor _*/ );
sword  oclose( /*_ struct cda_def *cursor _*/ );
sword  ocof  ( /*_ struct cda_def *lda _*/ );
sword  ocom  ( /*_ struct cda_def *lda _*/ );
sword  ocon  ( /*_ struct cda_def *lda _*/ );
sword  odefin( /*_ struct cda_def *cursor, sword pos, ub1 *buf,
                 sword bufl, sword ftype, sword scale, sb2 *indp,
                 text *fmt, sword fmtl, sword fmtt, ub2 *rlen, ub2 *rcode _*/ );
sword  odsc  ( /*_ struct cda_def *cursor, sword pos, sb2 *dbsize,
                 sb2 *fsize, sb2 *rcode, sb2 *dtype, sb1 *buf,
                 sb2 *bufl, sb2 *dsize _*/ );
sword  odescr( /*_ struct cda_def *cursor, sword pos, sb4 *dbsize,
                 sb2 *dbtype, sb1 *cbuf, sb4 *cbufl, sb4 *dsize,
                 sb2 *prec, sb2 *scale, sb2 *nullok _*/ );
sword  odessp( /*_ struct cda_def *cursor, text *objnam, size_t onlen,
              ub1 *rsv1, size_t rsv1ln, ub1 *rsv2, size_t rsv2ln,
              ub2 *ovrld, ub2 *pos, ub2 *level, text **argnam,
              ub2 *arnlen, ub2 *dtype, ub1 *defsup, ub1* mode,
              ub4 *dtsiz, sb2 *prec, sb2 *scale, ub1 *radix,
              ub4 *spare, ub4 *arrsiz _*/ );
sword  oerhms( /*_ struct cda_def *lda, sb2 rcode, text *buf,
                 sword bufsiz _*/ );
sword  oermsg( /*_ sb2 rcode, text *buf _*/ );
sword  oexec ( /*_ struct cda_def *cursor _*/ );
sword  oexfet( /*_ struct cda_def *cursor, ub4 nrows,
                 sword cancel, sword exact _*/ );
sword  oexn  ( /*_ struct cda_def *cursor, sword iters, sword rowoff _*/ );
sword  ofen  ( /*_ struct cda_def *cursor, sword nrows _*/ );
sword  ofetch( /*_ struct cda_def *cursor _*/ );
sword  oflng ( /*_ struct cda_def *cursor, sword pos, ub1 *buf,
                 sb4 bufl, sword dtype, ub4 *retl, sb4 offset _*/ );
sword  ologof( /*_ struct cda_def *lda _*/ );
sword  olon  ( /*_ struct cda_def *lda, text *uid, sword uidl,
                 text *pswd, sword pswdl, sword audit _*/ );
sword  oopen ( /*_ struct cda_def *cursor, struct cda_def *lda,
                 text *dbn, sword dbnl, sword arsize,
                 text *uid, sword uidl _*/ );
sword  oopt  ( /*_ struct cda_def *cursor, sword rbopt, sword waitopt _*/ );
sword  oname ( /*_ struct cda_def *cursor, sword pos, sb1 *tbuf,
                 sb2 *tbufl, sb1 *buf, sb2 *bufl _*/ );
sword  oparse( /*_ struct cda_def *cursor, text *sqlstm, sb4 sqllen,
                 sword defflg, ub4 lngflg _*/ );
sword  orlon ( /*_ struct cda_def *lda, ub1 *hda, text *uid,
                 sword uidl, text *pswd, sword pswdl, sword audit _*/ );
sword  orol  ( /*_ struct cda_def *lda _*/ );
sword  osql3 ( /*_ struct cda_def *cda, text *sqlstm, sword sqllen _*/ );
void sqlld2( /*_ struct cda_def *lda, text *cname, sb4 *cnlen _*/ );
void sqllda( /*_ struct cda_def *lda _*/ );


#endif  /* OCIKPR */
