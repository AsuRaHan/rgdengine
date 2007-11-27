#include "stdafx.h"

#include <engine/log/device.h>

namespace rgde
{
    namespace log
    {
        namespace device
        {
            file_wrapper::file_wrapper()
            {
            }

            file_wrapper::file_wrapper (const std::string &filename)
            {
                open(filename);
            }

            file_wrapper::~file_wrapper ()
            {
                close();
            }

            void file_wrapper::open (const std::string &filename)
            {
                if (m_file.is_open())
                    close();

                m_file.open(filename.c_str());
                m_file << "<html>\n<head>\n<meta http-equiv=Content-Type content='text/html; charset=windows-1251' />" \
                          "\n<style>\nbody {font-family: verdana; font-size: 9pt;}\n.id1 {width: 51pt;}\n</style>" \
                          "</head>\n<body>\n";
            }

            void file_wrapper::close ()
            {
                if (m_file.is_open())
                {
                    m_file << "</body></html>";
                    m_file.close();
                }
            }

            //������ � ���� multibyte-�����
            std::streamsize file_wrapper::write(const char *s, std::streamsize n)
            {
                if (!m_file.is_open())
                    return n; //��� ������� ������� 0 (�� ��� ���� �����������)?

                std::string in(s,n);
                std::string out;
                
                //������ '\n' �� "<br/>"
                while (!in.empty())
                {
                    std::string::size_type pos = in.find('\n');
                    if (pos == std::string::npos)
                    {
                        out += in;
                        in.erase();
                    }
                    else
                    {
                        out += in.substr(0, pos);
                        out += "</br>\n";
                        in = in.substr(pos+1);
                    }
                }

                m_file << out;
                return n;
            }

            //������ � ���� unicode-�����
            std::streamsize file_wrapper::write(const wchar_t *s, std::streamsize n)
            {
                if (!m_file.is_open())
                    return n; //��� ������� ������� 0 (�� ��� ���� �����������)?

                std::wstring in(s,n);
                std::wstring out;
                
                //������ '\n' �� "<br/>"
                while (!in.empty())
                {
                    std::wstring::size_type pos = in.find(L'\n');
                    if (pos == std::wstring::npos)
                    {
                        out += in;
                        in.erase();
                    }
                    else
                    {
                        out += in.substr(0, pos);
                        out += L"</br>\n";
                        in = in.substr(pos+1);
                    }
                }

                //������������� �� unicode � multibyte
                std::string buf;
                buf.resize(out.length());
				size_t num_chars = 0;

                //wcstombs_s(&num_chars, &buf[0], buf.size(), out.c_str(), buf.length());
				wcstombs(&buf[0], out.c_str(), buf.length());

                m_file << buf;
                return n;
            }

        }
    }
}