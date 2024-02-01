/**
 * 사용자로부터 들어온 신고를
 * 관리자에게 웹소켓으로 실시간으로 알려준다.
 * */
package com.project.poopkey.clientsocket;

import com.fasterxml.jackson.databind.ObjectMapper;
import org.springframework.web.socket.CloseStatus;
import org.springframework.web.socket.TextMessage;
import org.springframework.web.socket.WebSocketSession;
import org.springframework.web.socket.handler.TextWebSocketHandler;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class WebSocketReportHandler extends TextWebSocketHandler {

    // 일반적인 HttpMapping 방식으로 메시지를 전달받으면 웹소켓으로 알림을 전송하면 됨.
    // 이후 jwt 토큰 고유값에 대한 연동 작업도 필요.

    private final ObjectMapper objectMapper = new ObjectMapper();

    private List<WebSocketSession> sessions = new ArrayList<>();
//    private Map<WebSocketSession, long>

    @Override
    public void afterConnectionEstablished(WebSocketSession session) throws Exception {
        System.out.println("report 세션 연결+"+session);
        sessions.add(session);
    }

    @Override
    protected void handleTextMessage(WebSocketSession session, TextMessage message) throws Exception {
        super.handleTextMessage(session, message);
    }

    @Override
    public void afterConnectionClosed(WebSocketSession session, CloseStatus status) throws Exception {
        System.out.println("report 세션 해제+"+session);
        sessions.remove(session);
    }
}
