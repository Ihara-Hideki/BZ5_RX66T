/*
	-------------------------------
	----					   ----
	----  基本データ型の定義   ----
	----					   ----
	-------------------------------
	for SH7600
*/
#ifndef _FAR
	#define _FAR
#endif

/*	一般形式の表現	*/
typedef	  void					VOID;		/*	VOID型					*/
typedef	  void			 _FAR  *PVOID;		/*	VOID ポインタ型			*/
typedef	  const void	 _FAR  *PCVOID;		/*	const VOID ポインタ型	*/
typedef	  PVOID			 _FAR  *PPVOID;		/*	VOID ダブルポインタ型	*/
typedef	  const char			CONST_CHAR;
typedef	  CONST_CHAR	 _FAR  *PCONST_CHAR;
typedef	  PCONST_CHAR	 _FAR  *PPCONST_CHAR;
typedef	  char					CHAR;		/*	符号付き文字型			*/
typedef	  char			 _FAR  *PCHAR;		/*	符号付き文字ポインタ	*/
typedef	  PCHAR			 _FAR  *PPCHAR;		/*	符号付き文字ダブル		*/
typedef	  unsigned char			UCHAR;		/*	符号なし文字型			*/
typedef	  unsigned char	 _FAR  *PUCHAR;		/*	符号なし文字ポインタ	*/
typedef	  PUCHAR		 _FAR  *PPUCHAR;	/*	符号なし文字ダブル		*/
typedef	  short int				SHORT;		/*	符号付き短整数型		*/
typedef	  short int		 _FAR  *PSHORT;		/*	符号付き短整数ポインタ	*/
typedef	  unsigned short		USHORT;		/*	符号なし短整数型		*/
typedef	  unsigned short _FAR  *PUSHORT;	/*	符号なし短整数ポインタ	*/
typedef	  int					INTEGER;	/*	符号付き整数型			*/
typedef	  int			 _FAR  *PINT;		/*	符号付き整数型			*/
typedef	  unsigned int			UINT;		/*	符号なし整数型			*/
typedef	  unsigned int	 _FAR  *PUINT;		/*	符号なし整数ポインタ	*/
typedef	  long					LONG;		/*	符号付き長整数型		*/
typedef	  long			 _FAR  *PLONG;		/*	符号付き長整数ポインタ	*/
typedef	  unsigned long			ULONG;		/*	符号なし長整数型		*/
typedef	  unsigned long	 _FAR  *PULONG;		/*	符号なし長整数ポインタ	*/
typedef	  const char*		   *LPCTSTR;
/*	ビット長による表現	*/
typedef	  char					BYTE;		/*	符号付き８ﾋﾞｯﾄﾃﾞｰﾀ		*/
typedef	  char			 _FAR  *PBYTE;		/*	符号付き８ﾋﾞｯﾄﾎﾟｲﾝﾀ		*/
typedef	  unsigned char			UBYTE;		/*	符号なし８ﾋﾞｯﾄﾃﾞｰﾀ		*/
typedef	  unsigned char	 _FAR  *PUBYTE;		/*	符号なし８ﾋﾞｯﾄﾎﾟｲﾝﾀ		*/
typedef	  short int				WORD;		/*	符号付き１６ﾋﾞｯﾄﾃﾞｰﾀ	*/
typedef	  short int		 _FAR  *PWORD;		/*	符号付き１６ﾋﾞｯﾄﾎﾟｲﾝﾀ	*/
typedef	  unsigned short int	UWORD;		/*	符号なし１６ﾋﾞｯﾄﾃﾞｰﾀ	*/
typedef	  unsigned short int _FAR *PUWORD;	/*	符号なし１６ﾋﾞｯﾄﾎﾟｲﾝﾀ	*/
typedef	  long					DWORD;		/*	符号付き３２ﾋﾞｯﾄﾃﾞｰﾀ	*/
typedef	  long			 _FAR  *PDWORD;		/*	符号付き３２ﾋﾞｯﾄﾎﾟｲﾝﾀ	*/
typedef	  unsigned long			UDWORD;		/*	符号なし３２ﾋﾞｯﾄﾃﾞｰﾀ	*/
typedef	  unsigned long	 _FAR  *PUDWORD;	/*	符号なし３２ﾋﾞｯﾄﾎﾟｲﾝﾀ	*/
typedef	  double				REAL;		/*	浮動小数点データ		*/
typedef	  double		 _FAR  *PREAL;		/*	浮動小数点ポインタ		*/
typedef ULONG				(QWORD)[2];		/*	８バイト整数			*/

/*	ｱｲｻﾝｸ形式の表現 */
typedef	  unsigned char			uchar;		 /* 符号なし文字型		 */
typedef	  short int				sint;		 /* 符号付き短整数型	 */
typedef	  unsigned short int	usint;		 /* 符号なし短整数型	 */
typedef	  unsigned int			uint;		 /* 符号なし整数型		 */
typedef	  long					lint;		 /* 符号付き長整数		 */
typedef	  unsigned long			ulint;		 /* 符号なし長整数		 */
typedef	  unsigned char			*puchar;		 /* 符号なし文字型		 */
typedef	  short int				*psint;		 /* 符号付き短整数型	 */
typedef	  unsigned short int	*pusint;		 /* 符号なし短整数型	 */
typedef	  unsigned int			*puint;		 /* 符号なし整数型		 */
typedef	  long					*plint;		 /* 符号付き長整数		 */
typedef	  unsigned long			*pulint;		 /* 符号なし長整数		 */

