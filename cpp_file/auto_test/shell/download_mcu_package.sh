#!/usr/bin/expect
spawn svn co https://192.168.52.21/svn/Global5.0/11.测试/mcu_version_test/sdkag592eeu_lpm_test /home/xhh/auto_test/project/update_package/mcu_package
expect "guopenghui" {send "CX.gph2024\n"}
expect eof
