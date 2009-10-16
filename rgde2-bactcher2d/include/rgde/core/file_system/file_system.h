#pragma once

#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

// �������� ���������:
// ���� �������� �������
// ���� ��������� ������
// ��� ����� ����������
// ������ �������� ������ ����� �������� ����������� �������� ������ ����� (�������� ��� �������������)
// �����. ��� ������� ��������� ������ ���������� ���� ������ ������ � ������ ������. (�������� �������� ��������)
// �������:
// ������ ���� ���� �� 1 �������� ������ - �������� ������� ����� � �������� ���� �������� ����������
// ��������� �������� ����� �� ����� ����������� ������ (������� ������� � ���������������� �����������!!! ��� � �������, ����� ������� ��������!!!)
// ����������� ����� �������� ������� ��� �������� ��������� ���������, ���������, � ������������.
// ��� �� �������� ������ ������� �������� ������� ������ �� ������� ��������� ������, ���� ������ �� ����� ���������� 
// �� ����� �������� ������� ����� "data.pak"


namespace rgde
{
	typedef unsigned int uint;

	namespace file_system
	{
		namespace helpers
		{
			std::wstring get_file_name(const std::wstring& full_name);
			std::wstring get_file_ext(const std::wstring& full_name);
			std::wstring get_file_path(const std::wstring& full_name);

			bool is_file(const std::wstring& full_name) {return get_file_ext(full_name).length() != 0;}
			bool is_directory(const std::wstring& full_name) {return !is_file(full_name);}
		}

		struct stream
		{
			virtual ~stream() {}

			virtual uint get_position() const = 0;
			virtual bool set_position() = 0;
			virtual uint get_size() const = 0;
		};
		
		struct write_stream : public stream
		{
			virtual bool write(const char* const src, uint size) = 0;
		};		

		struct read_stream : public stream
		{
			/// return size of readed data
			virtual uint read(const char* dst, uint size) = 0;
		};

		typedef boost::shared_ptr<stream>		stream_ptr;
		typedef boost::shared_ptr<write_stream> write_stream_ptr;
		typedef boost::shared_ptr<read_stream>	read_stream_ptr;

		class file
		{
		public:
			virtual ~file(){}

			bool is_read_only() const {return m_read_only;}
			const std::wstring& get_full_name() const {return m_full_name;}

			virtual read_stream_ptr  open_read_stream() const = 0;

			/// returns empty pointer if READ_ONLY.
			virtual write_stream_ptr open_write_stream() = 0;

		protected:
			bool		 m_read_only;
			std::wstring m_full_name;
		};

		typedef boost::shared_ptr<file> file_ptr;

		struct file_source
		{
			virtual ~file_source() {}

			/// returns empty shared_ptr if file not found 
			virtual file_ptr find(const std::wstring& full_name) const = 0;

			virtual bool has_enumeration_support() const {return false;}
			virtual void enumerate(std::vector<file_ptr>& files, const std::wstring& path) const = 0;
		};

		typedef boost::shared_ptr<file_source> file_source_ptr;

		class file_system : boost::noncopyable
		{
		public:
			file_system();
			~file_system();

			void add_source(file_source_ptr source, uint priority = 0);

			/// returns empty shared_ptr if file not found 
			file_ptr find(const std::wstring& full_name) const;
			void enumerate(std::vector<file_ptr>& files, const std::wstring& path) const;

		protected:
			typedef std::vector<file_source_ptr> sources;
			sources m_sources;
		};
	}
}