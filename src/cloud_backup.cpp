#include "cloud_backup.hpp"
#include<thread>

// 压缩测试
void compress_test(char* argv[])
{
  // argv[1] = 源文件名称
  // argv[2] = 压缩包名称
  
  _cloud_sys::CompressUtil::Compress(argv[1], argv[2]);
  std::string file = argv[2];
  file += ".txt";
  _cloud_sys::CompressUtil::UnCompress(argv[2], file.c_str());
}
void data_test()
{
  
  _cloud_sys::DataManger data_manage("./test.txt");

  data_manage.InitLoad();
  data_manage.Insert("c.txt", "c.txt.gz");
  std::vector<std::string> list;
  // 获取所有信息测试
  data_manage.GetAllName(&list); // -----此处由于是输出型测试 list 必须加引用,否则报错
  for(auto i: list)
  {
    std::cout<< i << std::endl;
  }
  std::cout << "-------------" << std::endl;
  // 获取未压缩的文件名称测试
  list.clear();
  data_manage.NonCompressList(&list);

  for(auto i: list)
  {
    std::cout<< i << std::endl;
  }
  /*
  data_manage.Insert("a.txt", "a.txt");
  data_manage.Insert("b.txt", "b.txt.gz");
  data_manage.Insert("c.txt", "c.txt");
  data_manage.Insert("d.txt", "d.txt.gz");
  // 持久化存储
  data_manage.Storage();
  */
}
 
void m_non_compress()
{
  _cloud_sys::NonHotCompress ncom(GZFILE_DIR, BACKUP_DIR);
  ncom.Start();
  return;
}
void thr_http_server()
{
  _cloud_sys::Server srv;
  srv.Start();
  return;
}
int main(int argc, char* argv[])
{
  // 压缩包存放路径不存在, 则创建
  if(boost::filesystem::exists(GZFILE_DIR) == false)
  {
    boost::filesystem::create_directory(GZFILE_DIR);
  }
  // 文件备份路径不存在则创建
  if(boost::filesystem::exists(BACKUP_DIR) == false)
  {
    boost::filesystem::create_directory(BACKUP_DIR);
  }
  /*
  std::string s1("boost_1_53_0.zip");
  std::string s2("a.txt");
  _cloud_sys::data_manage.Insert(s2, s2);
  */

  // C++11 中的线程
  // 启动非热点压缩模块
  std::thread thr_compress(m_non_compress);
  // 启动网络通信服务模块
  std::thread thr_server(thr_http_server);
  
  // 等待线程退出
  thr_compress.join();
  thr_server.join(); 

  
  _cloud_sys::Server server;
  server.Start();
  
  //compress_test(argv);
  



  return 0;
}
