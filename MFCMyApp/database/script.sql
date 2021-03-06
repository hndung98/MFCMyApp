USE [master]
GO
/****** Object:  Database [Intern]    Script Date: 8/14/2020 3:01:40 PM ******/
CREATE DATABASE [Intern]
 CONTAINMENT = NONE
 ON  PRIMARY 
( NAME = N'Intern', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL15.SQLEXPRESS\MSSQL\DATA\Intern.mdf' , SIZE = 8192KB , MAXSIZE = UNLIMITED, FILEGROWTH = 65536KB )
 LOG ON 
( NAME = N'Intern_log', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL15.SQLEXPRESS\MSSQL\DATA\Intern_log.ldf' , SIZE = 8192KB , MAXSIZE = 2048GB , FILEGROWTH = 65536KB )
 WITH CATALOG_COLLATION = DATABASE_DEFAULT
GO
ALTER DATABASE [Intern] SET COMPATIBILITY_LEVEL = 150
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [Intern].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [Intern] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [Intern] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [Intern] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [Intern] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [Intern] SET ARITHABORT OFF 
GO
ALTER DATABASE [Intern] SET AUTO_CLOSE ON 
GO
ALTER DATABASE [Intern] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [Intern] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [Intern] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [Intern] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [Intern] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [Intern] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [Intern] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [Intern] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [Intern] SET  DISABLE_BROKER 
GO
ALTER DATABASE [Intern] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [Intern] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [Intern] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [Intern] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [Intern] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [Intern] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [Intern] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [Intern] SET RECOVERY SIMPLE 
GO
ALTER DATABASE [Intern] SET  MULTI_USER 
GO
ALTER DATABASE [Intern] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [Intern] SET DB_CHAINING OFF 
GO
ALTER DATABASE [Intern] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [Intern] SET TARGET_RECOVERY_TIME = 60 SECONDS 
GO
ALTER DATABASE [Intern] SET DELAYED_DURABILITY = DISABLED 
GO
ALTER DATABASE [Intern] SET QUERY_STORE = OFF
GO
USE [Intern]
GO
/****** Object:  UserDefinedFunction [dbo].[searchID]    Script Date: 8/14/2020 3:01:40 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE function [dbo].[searchID] (@condition nvarchar(10))
returns @table table(
	_id nvarchar(10),
	_uname nvarchar(50),
	_sname nvarchar(50),
	_email nvarchar(50),
	_falculty nvarchar(50),
	_company nvarchar(50)
)
as
begin
	insert into @table
	select id, username, s_name, email, falculty, company from student where id like '%' +@condition+'%'
	return;
end;
GO
/****** Object:  UserDefinedFunction [dbo].[searchName]    Script Date: 8/14/2020 3:01:40 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE function [dbo].[searchName](@condition nvarchar(50))
returns @table table(
	_id nvarchar(10),
	_uname nvarchar(50),
	_sname nvarchar(50),
	_email nvarchar(50),
	_falculty nvarchar(50),
	_company nvarchar(50)
)
as
begin
	insert into @table
	select id, username, s_name, email, falculty, company from student where s_name like '%' +@condition+'%'
	return;
end;
GO
/****** Object:  UserDefinedFunction [dbo].[searchScore]    Script Date: 8/14/2020 3:01:40 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
create function [dbo].[searchScore] (@condition nvarchar(50))
returns @table table(
	_id nvarchar(10),
	_sname nvarchar(50),
	_company nvarchar(50),
	_w1 int,
	_w2 int,
	_w3 int,
	_w4 int
)
as
begin
	insert into @table
	select id, s_name, company, week1, week2, week3, week4 from student where s_name like '%' +@condition+'%'
	return;
end;
GO
/****** Object:  UserDefinedFunction [dbo].[searchScoreID]    Script Date: 8/14/2020 3:01:40 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE function [dbo].[searchScoreID] (@condition nvarchar(10))
returns @table table(
	_id nvarchar(10),
	_sname nvarchar(50),
	_company nvarchar(50),
	_w1 int,
	_w2 int,
	_w3 int,
	_w4 int
)
as
begin
	insert into @table
	select id, s_name, company, week1, week2, week3, week4 from student where id like '%' +@condition+'%'
	return;
end;
GO
/****** Object:  Table [dbo].[company]    Script Date: 8/14/2020 3:01:40 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[company](
	[cname] [nvarchar](50) NOT NULL,
	[introduce] [nvarchar](100) NULL,
	[address] [nvarchar](50) NULL,
	[email] [nvarchar](50) NULL,
	[total_student] [int] NULL,
 CONSTRAINT [PK_company] PRIMARY KEY CLUSTERED 
(
	[cname] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[student]    Script Date: 8/14/2020 3:01:40 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[student](
	[id] [varchar](10) NOT NULL,
	[username] [varchar](30) NULL,
	[s_name] [nvarchar](50) NULL,
	[email] [nvarchar](50) NULL,
	[falculty] [nvarchar](50) NULL,
	[company] [nvarchar](50) NULL,
	[week1] [int] NULL,
	[week2] [int] NULL,
	[week3] [int] NULL,
	[week4] [int] NULL,
PRIMARY KEY CLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
INSERT [dbo].[company] ([cname], [introduce], [address], [email], [total_student]) VALUES (N'Bosch', N'ASP .NET, Python, Wordpress', N'quan Tan Binh', N'bosch@gmail.com', 1)
INSERT [dbo].[company] ([cname], [introduce], [address], [email], [total_student]) VALUES (N'Cube', N'Python, Java, C++', N'quan 12, TP HCM', N'cube@mail', 0)
INSERT [dbo].[company] ([cname], [introduce], [address], [email], [total_student]) VALUES (N'FPT', N'C++, C#, Java, Javascript, PHP', N'quan Binh Thanh, TP HCM', N'fpt@gmail.com', 3)
INSERT [dbo].[company] ([cname], [introduce], [address], [email], [total_student]) VALUES (N'GAPO', N'html, css, js, sql, java', N'quan 9  tp hcm', N'gapo@mail', 4)
INSERT [dbo].[company] ([cname], [introduce], [address], [email], [total_student]) VALUES (N'HKTect', N'Ruby On Rails', N'quan Tan Binh, TP HCM', N'hk@mail', 0)
INSERT [dbo].[company] ([cname], [introduce], [address], [email], [total_student]) VALUES (N'IVC', N'C, C++', N'quan Tan Binh, TP HCM', N'ivc@mail', 0)
INSERT [dbo].[company] ([cname], [introduce], [address], [email], [total_student]) VALUES (N'Logitech', N'Python, Java.', N'Quan 10 TP HCM', N'logi@mail', 1)
INSERT [dbo].[company] ([cname], [introduce], [address], [email], [total_student]) VALUES (N'Sorimachi', N'MFC, ASP .NET, Python', N'Hoang Hoa Tham, q. Tan Binh', N'sorimachi@gmail.com', 6)
INSERT [dbo].[company] ([cname], [introduce], [address], [email], [total_student]) VALUES (N'Viettel', N'Network, Java', N'quan 7, TP HCM', N'vt@gmail', 3)
INSERT [dbo].[company] ([cname], [introduce], [address], [email], [total_student]) VALUES (N'Viettel Telecom', N'Java, Python', N'quan 7, TP HCM', N'viettel@gmail.com', 1)
INSERT [dbo].[company] ([cname], [introduce], [address], [email], [total_student]) VALUES (N'Vina Game', N'Android Java, Unity C#', N'quan 7, TP HCM', N'vinagame@mail', 1)
INSERT [dbo].[student] ([id], [username], [s_name], [email], [falculty], [company], [week1], [week2], [week3], [week4]) VALUES (N'123', N'Pep', N'Alan Becker', N'alan@mail', N'Computer Engineering', N'GAPO', 5, 6, 7, 8)
INSERT [dbo].[student] ([id], [username], [s_name], [email], [falculty], [company], [week1], [week2], [week3], [week4]) VALUES (N'1234', N'Pep', N'h dung', N'hd@mail.com', N'Computer Science', N'GAPO', 0, 0, 0, 0)
INSERT [dbo].[student] ([id], [username], [s_name], [email], [falculty], [company], [week1], [week2], [week3], [week4]) VALUES (N'16101', N'Sane', N'Bruno Fernandes', N'brunol@gmail.com', N'Computer Science', N'Sorimachi', 6, 7, 7, 8)
INSERT [dbo].[student] ([id], [username], [s_name], [email], [falculty], [company], [week1], [week2], [week3], [week4]) VALUES (N'16104', N'Pep', N'Leo Messi', N'messi@mail.com', N'Computer Science', N'Bosch', 8, 9, 10, 8)
INSERT [dbo].[student] ([id], [username], [s_name], [email], [falculty], [company], [week1], [week2], [week3], [week4]) VALUES (N'16106', N'Pep', N'Mason Greenwood', N'mason@mail.com', N'Computer Science', N'Viettel Telecom', 6, 8, 6, 7)
INSERT [dbo].[student] ([id], [username], [s_name], [email], [falculty], [company], [week1], [week2], [week3], [week4]) VALUES (N'16107', N'Pep', N'De Jong', N'dejong@mail', N'Computer Science', N'Sorimachi', 4, 2, 0, 0)
INSERT [dbo].[student] ([id], [username], [s_name], [email], [falculty], [company], [week1], [week2], [week3], [week4]) VALUES (N'16108', N'Pep', N'Paulo Dybala', N'dybala@mail', N'Computer Engineering', N'Sorimachi', 6, 6, 6, 7)
INSERT [dbo].[student] ([id], [username], [s_name], [email], [falculty], [company], [week1], [week2], [week3], [week4]) VALUES (N'16110', N'Pep', N'Kaka', N'kaka@mail', N'Computer Engineering', N'Sorimachi', 8, 9, 9, 9)
INSERT [dbo].[student] ([id], [username], [s_name], [email], [falculty], [company], [week1], [week2], [week3], [week4]) VALUES (N'16111', N'Pep', N'Leroy Sane', N'sane@mail', N'Computer Engineering', N'FPT', -1, -1, -1, -1)
INSERT [dbo].[student] ([id], [username], [s_name], [email], [falculty], [company], [week1], [week2], [week3], [week4]) VALUES (N'16112', N'Pep', N'Kai Havertz', N'kaiz@gmail.com', N'Computer Science', N'Sorimachi', 3, 2, 3, 4)
INSERT [dbo].[student] ([id], [username], [s_name], [email], [falculty], [company], [week1], [week2], [week3], [week4]) VALUES (N'16113', N'Pep', N'Mesut Ozil', N'ozil@mail', N'Computer Science', N'FPT', -1, -1, -1, -1)
INSERT [dbo].[student] ([id], [username], [s_name], [email], [falculty], [company], [week1], [week2], [week3], [week4]) VALUES (N'16114', N'Pep', N'De Bruyne', N'kevin@gmail', N'Computer Science', N'Sorimachi', 8, 8, 8, 8)
INSERT [dbo].[student] ([id], [username], [s_name], [email], [falculty], [company], [week1], [week2], [week3], [week4]) VALUES (N'16115', N'Pep', N'Ilkay Gundogan', N'ilkay@gmail', N'Computer Engineering', N'Viettel', 7, 6, 7, 7)
INSERT [dbo].[student] ([id], [username], [s_name], [email], [falculty], [company], [week1], [week2], [week3], [week4]) VALUES (N'16117', N'Pep', N'Cris Ronaldo', N'cr@mail', N'Computer Engineering', N'FPT', -1, -1, -1, -1)
INSERT [dbo].[student] ([id], [username], [s_name], [email], [falculty], [company], [week1], [week2], [week3], [week4]) VALUES (N'16118', N'Pep', N'Mason Mount', N'mount@mail', N'Computer Engineering', N'Viettel', -1, -1, -1, -1)
INSERT [dbo].[student] ([id], [username], [s_name], [email], [falculty], [company], [week1], [week2], [week3], [week4]) VALUES (N'16119', N'Pep', N'Lukaku', N'kukaku@gmail.com', N'Computer Engineering', N'Vina Game', -1, -1, -1, -1)
INSERT [dbo].[student] ([id], [username], [s_name], [email], [falculty], [company], [week1], [week2], [week3], [week4]) VALUES (N'16120', N'Pep', N'Lauzaro', N'laza@mail', N'Computer Science', N'GAPO', 4, 6, 8, 8)
INSERT [dbo].[student] ([id], [username], [s_name], [email], [falculty], [company], [week1], [week2], [week3], [week4]) VALUES (N'16121', N'Pep', N'Ivan Perisic', N'ivan@mail', N'Computer Science', N'GAPO', -1, -1, -1, -1)
INSERT [dbo].[student] ([id], [username], [s_name], [email], [falculty], [company], [week1], [week2], [week3], [week4]) VALUES (N'16122', N'Pep', N'Dani Olmo', N'olmo@mail', N'Computer Science', N'Logitech', -1, -1, -1, -1)
INSERT [dbo].[student] ([id], [username], [s_name], [email], [falculty], [company], [week1], [week2], [week3], [week4]) VALUES (N'16123', N'Pep', N'N''golo Kante', N'kante@mail', N'Computer Engineering', N'Viettel', -1, -1, -1, -1)
ALTER TABLE [dbo].[company] ADD  CONSTRAINT [DF_company_total_student]  DEFAULT ((0)) FOR [total_student]
GO
ALTER TABLE [dbo].[student] ADD  CONSTRAINT [DF_student_week1]  DEFAULT ((-1)) FOR [week1]
GO
ALTER TABLE [dbo].[student] ADD  CONSTRAINT [DF_student_week2]  DEFAULT ((-1)) FOR [week2]
GO
ALTER TABLE [dbo].[student] ADD  CONSTRAINT [DF_student_week3]  DEFAULT ((-1)) FOR [week3]
GO
ALTER TABLE [dbo].[student] ADD  CONSTRAINT [DF_student_week4]  DEFAULT ((-1)) FOR [week4]
GO
ALTER TABLE [dbo].[student]  WITH CHECK ADD  CONSTRAINT [fk_student_company] FOREIGN KEY([company])
REFERENCES [dbo].[company] ([cname])
ON UPDATE CASCADE
ON DELETE CASCADE
GO
ALTER TABLE [dbo].[student] CHECK CONSTRAINT [fk_student_company]
GO
USE [master]
GO
ALTER DATABASE [Intern] SET  READ_WRITE 
GO
