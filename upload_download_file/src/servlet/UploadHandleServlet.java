package servlet;

import java.io.File;
import java.io.IOException;
import java.util.Iterator;
import java.util.List;
import java.util.UUID;

import javax.servlet.ServletException;
import javax.servlet.http.*;

import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.FileItemFactory;
import org.apache.commons.fileupload.FileUploadException;
import org.apache.commons.fileupload.disk.*;
import org.apache.commons.fileupload.servlet.ServletFileUpload;

public class UploadHandleServlet extends HttpServlet
{

	
	protected void doPost(HttpServletRequest request,HttpServletResponse response)throws ServletException,IOException{
		
			 response.setContentType("text/html;charset=gbk");
			 //检查文件上传请求是否使用multipart/form-data
			 boolean isMultipart = ServletFileUpload.isMultipartContent(request);
			 if(!isMultipart){
				 //报错
				 return ;
			 }
			 //create a factory for disk-based file items
			 FileItemFactory factory = new DiskFileItemFactory();
			 //创建一个文件上传处理器实例
			 ServletFileUpload upload = new ServletFileUpload(factory);
			 
			 List<FileItem> items = null;
			 try{
				
				 //使用处理器对请求进行解析，会把消息体中的每一块
				 //解析成一个FileItem对象
				 items = upload.parseRequest(request);
			 }catch(FileUploadException e){
				 e.printStackTrace();
			 }
			 
			 if(items == null){
				 return;
			 }
			 Iterator<FileItem> it = items.iterator();
			 while(it.hasNext()){//处理FileItem
				 FileItem fileitem = (FileItem)it.next();
				 if(fileitem.isFormField()){//如果是普通的表单输入域
					 String name = fileitem.getFieldName();//获取普通参数名
					 String value = fileitem.getString();//参数对应的值
					 //对值进行转码，防止中文乱码
					 value = new String(value.getBytes("gbk"));
					 System.out.println(name+"="+value);
				 }else{//是文件上传域的话
					 String filename = fileitem.getName();//获取上传文件名
					 //获取上传文件mime类型
					 String contentType = fileitem.getContentType();
					 //获取上传的文件大小（字节）
					 long size = fileitem.getSize();
					 
					 //获取存放上传文件的真实目录
					 String basePath = request.getServletContext().getRealPath("/files");
					 //获取文件名后缀
					 String extend = filename.substring(filename.lastIndexOf("."));
					 
					 String newName = filename + extend;
					 
					 File file = new File(basePath,newName);//创建一个目标文件
					 try{
						 System.out.println(file);
						 fileitem.write(file);//把上传的文件内容写到目标文件中
						 response.getWriter().println("文件上传成功");
						 response.getWriter().println(file.getAbsolutePath());
					 }catch(Exception e){
						 e.printStackTrace();
					 }
				 }
			 }
		
		
		
		
	}
	
	
	
}
