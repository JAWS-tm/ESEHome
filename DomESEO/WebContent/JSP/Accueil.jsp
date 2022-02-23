<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<title>Accueil - DomESEO</title>
	<link rel="stylesheet" href="CSS/Body.css">
	<link rel="stylesheet" href="CSS/Accueil.css">
</head>
<body>
	<%@include file="Header.jsp" %>
	<video id="bgVideo" preload="true" autoplay loop muted>
      	<source src="CSS/video/test.mp4" type="video/mp4" >
  	</video>
	<div id="body">
		<%--<c:if test="${ connecte == 'oui' }">
			<%@include file="User_Dashboard.jsp" %>
		</c:if>
		<c:if test="${ connecte != 'oui' }">
			<%@include file="Visiteur_Dashboard.jsp" %>
		</c:if>--%>
	</div>
</body>
</html>