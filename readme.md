# STM32 BootLoader与APP整合工具

- 软件版本：Release V1.0.0.1

- 工具说明：

  控制台工具：CombinBinFile.exe

  - 使用方法：loader路径+空格+APP路径+空格+APP地址（16进制）
  - 输出路径：exe所在目录

  GUI版本：BinMergeTool.exe

- 输出文件名格式

  app文件名（loader文件名）.bin

- 程序开发平台：VS2019

- 语言特性：C++14

- 测试文件目录结构

  Testfiles------|

  ​                      |---------SHT_20200930_A0.bin（app文件）

  ​                      |---------SHT_Loader_20200914.bin（loader文件）

​                             |---------SHT_20200930_A0(SHT_Loader_20200914).bin（loader+app整合文件）