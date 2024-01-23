package com.project.poopkey.handler;

import com.project.poopkey.model.service.render.FloorCongestionService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.socket.CloseStatus;
import org.springframework.web.socket.TextMessage;
import org.springframework.web.socket.WebSocketSession;
import org.springframework.web.socket.handler.TextWebSocketHandler;

@Configuration // 이 주석이 문제없으면 삭제하기
public class ClientSocketHandler extends TextWebSocketHandler {

    @Autowired
    private FloorCongestionService floorCongestionService;

    private WebSocketSession webSocketSession = null; // 연결된 웹소켓 세션

    @Override
    public void afterConnectionEstablished(WebSocketSession session) throws Exception {
        System.out.println("connection established!");
        System.out.println("sessionId: "+session.getId());
        webSocketSession = session;
    }

    // 클라이언트가 실시간으로 전달받아야되는 정보 : 화장실지도 렌더링, 관리자일때 푸시알림
    @Override
    protected void handleTextMessage(WebSocketSession session, TextMessage message) throws Exception {
        super.handleTextMessage(session, message);
    }

    @Override
    public void afterConnectionClosed(WebSocketSession session, CloseStatus status) throws Exception {
        webSocketSession.close(); // 웹소켓 연결 종료
    }
}
