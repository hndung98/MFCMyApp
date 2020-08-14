Link project on github:	https://github.com/hndung98/MFCMyApp

Use script.sql to create database or mdf file (sql server, ver 2019)

Change  connecting strings in source code of this project at:
	- CompanyManagement.cpp: StartDialog function, line 68
	- ScoreTable.cpp: StartDialog function, line 94
	- StudentManagement.cpp: StartDialog function, line 89
The connecting string like: "DRIVER={SQL Server};SERVER=server_name;DATABASE=database_name;Trusted_Connection=yes;"