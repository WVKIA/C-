<%@ page language="java" contentType="text/html; charset=gbk"
    pageEncoding="gbk"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gbk">
<title>Insert title here</title>
</head>
<body>
<form action="UploadHandleServlet" method="post" enctype="multipart/form-data">

<table>
	<tr>
		<td>selet file</td>
		<td><input type="file" multiple name="src"></td>
	</tr>
	<tr>
		<td>description</td>
		<td><textarea name="summary" rows="4" cols="30"></textarea></td>
	</tr>
	<tr>
		<td colspan="2"><input type="submit" value="tijiao"></td>
	</tr>
</table>

</form>

</body>
</html>