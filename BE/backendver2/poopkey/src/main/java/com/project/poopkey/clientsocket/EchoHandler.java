package com.project.poopkey.clientsocket;

import org.springframework.web.socket.CloseStatus;
import org.springframework.web.socket.TextMessage;
import org.springframework.web.socket.WebSocketSession;
import org.springframework.web.socket.handler.TextWebSocketHandler;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class EchoHandler extends TextWebSocketHandler {
    List<WebSocketSession> sessions = new ArrayList<>();
    Map<String, WebSocketSession> userSession = new HashMap<>();

    @Override
    public void afterConnectionEstablished(WebSocketSession session) throws Exception {
        System.out.println("user 세션과 연결됨: "+session);
    }

    @Override
    protected void handleTextMessage(WebSocketSession session, TextMessage message) throws Exception {
        super.handleTextMessage(session, message);
    }

    @Override
    public void afterConnectionClosed(WebSocketSession session, CloseStatus status) throws Exception {
        sessions.remove(session);
        System.out.println("웹소켓 연결이 종료됨");
    }
}

////클라이언트 접속 성공 시 연결 성공시
//@Override
//public void afterConnectionEstablished(WebSocketSession session) throws Exception{
//    System.out.println("afterConnectionEstablished:" + session);
//
//    //userId 알아내기
//    Map<String, Object> sessionVal =  session.getAttributes();
//    SysLog0101VO sysLog0101VO = (SysLog0101VO) sessionVal.get("sysLog0101VO");
//    System.out.println(sysLog0101VO.getUserId());
//    String userId = sysLog0101VO.getUserId();
//
//    if(userSessions.get(userId) != null) {
//        //userId에 원래 웹세션값이 저장되어 있다면 update
//        userSessions.replace(userId, session);
//    } else {
//        //userId에 웹세션값이 없다면 put
//        userSessions.put(userId, session);
//    }
//}