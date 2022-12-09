# uos-children-daemon
 -  学生版的DBus服务：
    -  读写配置文件的后台
    -  读写数据库的后台
    -  鉴权上传同步的逻辑
    -  护眼健康的后台
    -  浏览器插件依赖的后台程序

## 编译依赖

```bash
sudo apt install cmake debhelper libdtkwidget-dev libdtkgui-dev libqt5webchannel5-dev qtwebengine5-dev pkg-config qttools5-dev-tools qttools5-dev libssl-dev libdframeworkdbus-dev libglib2.0-dev libsecret-1-dev libqt5xmlpatterns5-dev libgsettings-qt-dev qtmultimedia5-dev
```

## 运行依赖

```bash
sudo apt install libqt5widgets5
```

## 编译安装

### 编译

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```

### 安装

```bash
$ sudo make install
```

## 目录结构

|目录结构|说明|
:----|:----:|
| src/children-guard-session-daemon |鉴权、护眼健康、绑定解绑的后台接口进程|
| src/children-guard-session-daemon/config |session dbus 的service文件|
| src/children-guard-system-daemon |配置文件和数据库的读写、开关dbus模式的后台的进程|
| src/children-guard-system-daemon/config |system dbus 的service文件、默认的配置文件、数据同步更新的时候写入古诗词数据库的sql文件|
| src/uos-children-guard-native |浏览器依赖的后台进程|

## 注意事项

- 正式环境和测试环境切换
  - 测试环境
    - mkdir -p /.config/children-guard/
    - touch environment
    - echo DEEPIN_PRE= ~/.config/children-guard/environment
  - 正式环境
    - rm -f ~/.config/children-guard/environment
