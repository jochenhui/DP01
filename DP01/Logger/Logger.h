//
//  Logger.h
//  fmcore
//
//  Created by shigw on 15/6/14.
//  Copyright (c) 2015年 史光伟. All rights reserved.
//

#ifndef __fmcore__Logger__
#define __fmcore__Logger__

#include <stdio.h>
#include "_CLocker.h"

namespace NS_FEIMA {
	const int 	LOG_NONE		= 0;
	const int 	LOG_EMERGENCY	= 1;
	const int 	LOG_CRITICAL	= 2;
	const int 	LOG_ERROR		= 3;
	const int 	LOG_WARNING		= 4;
	const int 	LOG_INFO		= 5;
	const int 	LOG_DEBUG		= 6;

	class CLogger : public _CLocker
	{
	public:
		CLogger();
		~CLogger();
		char *	InitLogger(const char *sPath,const char *sBaseName,const char *sExtName,char *sDestNmae=NULL);
		FILE *	OpenLogger(const char *sPath,char *sMsg=NULL);
		FILE *  OpenLogger(char *sErr=NULL);
		void	CloseLogger(FILE *fh=NULL);
		void	FlushLogger();
		void ReportEvents(int iLevel,const char *sType,const char *sFormat,...);
	private:
		char 	 m_sName[1024];
		FILE	*m_fh;
		
		const char *m_LogString[7];
		void 	 f_init();
		void 	 f_done();
	};
	
}
#endif /* defined(__fmcore__Logger__) */
