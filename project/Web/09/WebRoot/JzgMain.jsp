<%@ page language="java" pageEncoding="gb2312"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jstl/core_rt"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<script language="javascript">
	function openHref(main,child){					
		parent.topMenuFrame.location.href=main;
	}
</script>
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=gb2312" />
		<title>Centered Sliding Doors Navigation at exploding-boy.com</title>
		<link href="css/main.css" rel="stylesheet">
	</head>

	<body>
		<div id="navigation">
			<ul>
				<c:if test="${sessionScope.loginUser!=null&&sessionScope.loginUser.username=='mr' }">
					<!-- CSS Tabs -->
<li <c:if test="${param.action=='se'}"> id="current" </c:if>>
	<a href="courseEmployeeLoader.htm" target="mainFrame"
	onClick="openHref('JzgMain.jsp?action=se')"><span>教职任课</span>
	</a>
</li>
<li <c:if test="${param.action=='ce'}"> id="current" </c:if>>
	<a href="chargeEmployeeLoader.htm" target="mainFrame"
	onClick="openHref('JzgMain.jsp?action=ce')"><span>任班主任</span>
	</a>
</li>
<li <c:if test="${param.action=='stc'}"> id="current" </c:if>>
	<a href="searchTeaCourseEmployeeLoader.htm" target="mainFrame"
	onClick="openHref('JzgMain.jsp?action=stc')"><span>任课教师查询</span>
	</a>
</li>
<li <c:if test="${param.action=='sce'}"> id="current" </c:if>>
	<a href="searchChargeEmployeeLoader.htm" target="mainFrame"
	onClick="openHref('JzgMain.jsp?action=sce')"><span>班主任查询</span>
	</a>
</li>
				</c:if>
				<c:if test="${sessionScope.loginUser==null||sessionScope.loginUser.username!='mr' }">
					<li>
						<a href="Content.jsp" target="mainFrame"><span>您未登录或权限不够，请重新登录系统。</span>
						</a>
					</li>
				</c:if>
			</ul>
		</div>
	</body>
</html>
