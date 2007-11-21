#pragma once

#include <engine/log/device.h>
#include <boost/iostreams/stream.hpp>

namespace rgde
{
    namespace log
    {
        typedef boost::iostreams::stream<device::composite_dev<char> >    log_stream;
        typedef boost::iostreams::stream<device::composite_dev<wchar_t> > wlog_stream;

        //multibyte
        extern log_stream lmsg;
        extern log_stream lwrn;
        extern log_stream lerr;

        //unicode
        extern wlog_stream wlmsg;
        extern wlog_stream wlwrn;
        extern wlog_stream wlerr;

        //����� ��� ���������� ������ � �����:
        //  ���� ���������� ���� ���� ��������� ����� ������,
        //  ����������� ��������������� ����������� ������� (w)cout � (w)cerr � ���
        class logsystem
        {
        public:
            logsystem();
           ~logsystem();

        private:
            //������������� ������������� ������ ������ ���������� ����� ������
            class loghelper
            {
            public:
                loghelper();
               ~loghelper();

            private:
                //��������� �� ����������� ������
                std::streambuf  *coutsbuf;
                std::wstreambuf *wcoutsbuf;

                std::streambuf  *cerrsbuf;
                std::wstreambuf *wcerrsbuf;

                static std::string generateLogName();

            private:
                loghelper (const loghelper&);
                loghelper& operator= (const loghelper&);
            };

            static int counter;
            static loghelper *ploghelper;

        private:
            logsystem (const logsystem&);
            logsystem& operator= (const logsystem&);
        };
    }
}