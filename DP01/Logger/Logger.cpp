//
//  Logger.cpp
//  fmcore
//
//  Created by shigw on 15/6/14.
//  Copyright (c) 2015年 史光伟. All rights reserved.
//

#include "Logger.h"
#include <string.h>
#include <time.h>
#include <stdarg.h>

using namespace NS_FEIMA;

CLogger::CLogger()
{
	f_init();
}

CLogger::~CLogger()
{
	f_done();
}

void CLogger::f_init()
{
	strcpy_s(m_sName,sizeof(m_sName),"");
	m_fh = NULL;

	m_LogString[LOG_NONE]		="";
	m_LogString[LOG_EMERGENCY]	="EMERGENCY";
	m_LogString[LOG_CRITICAL]	="CRITICAL";
	m_LogString[LOG_ERROR]		="ERROR";
	m_LogString[LOG_WARNING]	="WARNING";
	m_LogString[LOG_INFO]		="INFO";
	m_LogString[LOG_DEBUG]		="DEBUG";
}

void CLogger::f_done()
{
	if (m_fh)
		fclose(m_fh);
	m_fh = NULL;
}

char *CLogger::InitLogger(const char *sPath, const char *sBaseName, const char *sExtName,char *sDestName)
{
	time_t	now;
	struct tm	*timeinfo,timeinfo_buffer;
	int		iLen;
	char		m_sPath[1024];//20160905
	char		m_sTime[80];

#pragma warning(push)
#pragma warning(disable:4996)
	strncpy(m_sPath,sPath,sizeof(m_sPath)-1);
#pragma warning(pop)
	iLen = (int)strlen(m_sPath);
	if (iLen)
	{
		if (m_sPath[iLen-1]!='\\' &&
			m_sPath[iLen-1]!='/')
			strcat_s(m_sPath,sizeof(m_sPath),"/");
	}
	
	strcat_s(m_sPath,sizeof(m_sPath),sBaseName);
	
	time(&now);

	errno_t err ;

	err=localtime_s(&timeinfo_buffer,&now);
	timeinfo = &timeinfo_buffer;
	strftime(m_sTime,80,"%Y%m%d%H%M%S",timeinfo);
	strcat_s(m_sPath,sizeof(m_sPath),m_sTime);
	if (strlen(sExtName))
	{
		if (sExtName[0] != '.')
			strcat_s(m_sPath,sizeof(m_sPath),".");
	}
	strcat_s(m_sPath,sizeof(m_sPath),sExtName);
	if (sDestName == NULL)
		sDestName = m_sName;
	strcpy_s(sDestName,sizeof(m_sName),m_sPath);
	return sDestName;
}


FILE *CLogger::OpenLogger(const char *sPath,char *sMsg)
{
	FILE *fh;

	fh = NULL;
	fh = fopen(sPath,"a+");
	if (fh == NULL)
	{
		if (sMsg)
			sprintf_s(sMsg,1024,"Can not open logfile:%s",sPath);
		return NULL;
	}
	m_fh = fh;
	return fh;
}
FILE *CLogger::OpenLogger(char *sErr)
{
	return OpenLogger(m_sName,sErr);
}

void CLogger::CloseLogger(FILE *fh)
{
	if(fh == NULL)
	{
		if (m_fh == NULL)
			return;
		fclose(m_fh);
		m_fh = NULL;
		return;
	}
	fclose(fh);
}
void CLogger::ReportEvents(int iLevel,const char *sType,const char *sFormat,...)
{
	char 	m_sBuffer[4096];
	time_t	now;
	struct tm *timeinfo;
	struct tm dummy;
	
	Lock();
	time(&now);

	errno_t err;
	err=localtime_s(&dummy,&now);
	timeinfo = &dummy;
	strftime(m_sBuffer,80,"%Y%m%d%H%M%S:",timeinfo);
	
	if (iLevel < 0 || iLevel > LOG_DEBUG)
	{
		sprintf_s(m_sBuffer+strlen(m_sBuffer),sizeof(m_sBuffer)-strlen(m_sBuffer),"Level(%d)",iLevel);
	}
	else
	{
		sprintf_s(m_sBuffer+strlen(m_sBuffer),sizeof(m_sBuffer)-strlen(m_sBuffer),"%s ",m_LogString[iLevel]);
	}
	
	va_list v;
	va_start(v,sFormat);
	vsprintf_s(m_sBuffer+strlen(m_sBuffer),sizeof(m_sBuffer)-strlen(m_sBuffer),sFormat,v);
	va_end(v);
	
	fprintf(stdout,"%s\n",m_sBuffer);
	if (m_fh != NULL)
		fprintf(m_fh,"%s\n",m_sBuffer);
	fflush(m_fh);
	UnLock();
}
void CLogger::FlushLogger()
{
	if (m_fh)
		fflush(m_fh);
}
