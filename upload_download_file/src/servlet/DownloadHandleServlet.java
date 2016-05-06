package servlet;

import java.io.*;
import java.net.URLEncoder;

import javax.servlet.*;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.omg.CORBA_2_3.portable.OutputStream;

public class DownloadHandleServlet extends HttpServlet
{
	protected void doGet(HttpServletRequest request,HttpServletResponse response)throws ServletException,IOException
	{
		String path = request.getParameter("filename");//获取请求下载的文件名
		//超链接属于get请求，服务器默认使用ISO-8859-1编码传递链接参数
		//参见server.xml的urlencoding设置
		
		String usedname = path;
		path = request.getServletContext().getRealPath("/")+path;
		path = new String(path.getBytes("gbk"),"gbk");//转码
		
		path = java.net.URLDecoder.decode(path,"gbk");
		
		File file = new File(path);
		InputStream in = new FileInputStream(file);
		byte[] buffer  =new byte[in.available()];
		in.read(buffer);
		response.reset();
		ServletOutputStream os = response.getOutputStream();
		response.addHeader("Content-Disposition", "attachment;filename="
				+new String(usedname));
		response.addHeader("Content-Length", ""+file.length());
		response.setContentType("application/octet-stream");
		System.out.println(response.getHeaderNames());
		os.write(buffer);
		os.flush();
		os.close();
		in.close();
		
	}
	
}
