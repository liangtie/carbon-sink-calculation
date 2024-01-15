# carbon-sink-calculation

This is the carbon-sink-calculation project.

# Building and installing

See the [BUILDING](BUILDING.md) document.

# Contributing

See the [CONTRIBUTING](CONTRIBUTING.md) document.

# Licensing

<!--
Please go to https://choosealicense.com/licenses/ and choose a license that
fits your needs. The recommended license for a project of this type is the
GNU AGPLv3.
-->

1、注册时只保留普通用户选项 ；2、电脑版的名称改为：城市建筑碳汇量计算系统；3、电脑版管理员账号登入进去没有账号管理选项；4、电脑版缺少查看历史数据一栏，点击进入历史数据，可以看到之前计算的数据，再在这里导出Excel

接口
application/json  json格式上传

http://101.200.162.174:8088/";
 
1、添加用户的接口   user/insert   （Json格式 post 请求）
   name     姓名
   account  账号
   role       3（固定的）
   password       密码
   createTime   创建时间 （YY-MM-dd HH:mm:ss）
   company       所属单位
   
 2、用户列表查询  user/pageList  （无入参） （GET 请求）
 
 3、删除用户  user/delete      （post 请求）    url 后排拼接 用户id （用户id 为列表数据可获取）
 4、修改密码  user/delete      （post 请求）    url 后排拼接 用户id （用户id 为列表数据可获取）  
5、提交 计算结果接口  calculate/insert  （Json格式 post 请求）

  province 省
  city  市
  county 区  
  architecturalType  城市建筑类型
  cementType            水泥类型
  cementLevel                    水泥强度等级
  concreteLevel   混凝土强度等级
      structureType             建筑结构类型
	  
	  structureTime        建成时间
	  structureArea                   建筑基地⾯积
		structureLine				  建筑基地周
		structureNum				   建筑层数
		structureHigh				   建筑层高
		structureCount				   建筑数量(栋)
		calculateResult				   计算结果（kg）
		createTime                     计算时间 yyyy-MM-dd HH:mm:ss
		userId                             用户ID
		

6  获取历史计算结果 calculate/pageList";  （Json格式 post 请求）

userId   用户Id    登录接口返回

role   角色Type

7、    登录接口       user/login    （Json格式 post 请求）

account 账号
password 密码
 
