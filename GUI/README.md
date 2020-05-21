### 运行环境

JDK1.8

### 安装并配置JDK1.8

```bash
//解压
cd /usr/lib
sudo mkdir jdk
sudo tar -zxvf jdk-8u251-linux-x64.tar.gz
sudo mv ./jdk1.8.0_251 ./jdk

//环境配置
sudo vi /etc/profile
在末尾添加：
#set java env
export JAVA_HOME=/usr/lib/jdk/jdk1.8.0_251
export JRE_HOME=${JAVA_HOME}/jre    
export CLASSPATH=.:${JAVA_HOME}/lib:${JRE_HOME}/lib    
export PATH=${JAVA_HOME}/bin:$PATH 
//生效
source /etc/profile

配置软连接
sudo update-alternatives --install /usr/bin/java  java  /usr/lib/jdk/jdk1.8.0_251/bin/java 300
sudo update-alternatives --install /usr/bin/javac  javac  /usr/lib/jdk/jdk1.8.0_251/bin/javac 300

测试是否成功
java -version
```

### 运行

> FileTransUtil-User1 
>
> FileTransUtil-User2
>
> 为模拟的两个终端实体，可以分别发送和接收文件（实质上内容完全一样）

```bash
cd FileTransUtil-User1
chmod +777 run.sh 
双击运行脚本run.sh即可打开GUI
//若不能打开请参考：https://blog.csdn.net/miffywm/article/details/103382405
```

### 流程

发送文件：

打开User1，运行`run.sh`， 输入IP和端口号（IP格式：`x.x.x.x`），选择文件，点击`Send`

接收文件：

打开User2，运行`run.sh`， 输入IP和端口号（IP格式：`x.x.x.x`），点击 `Rec`

**若发送成功可在User2的文件夹下接收到文件，并且两个GUI窗口会退出**

