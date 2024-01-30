package com.project.poopkey.clientsocket;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.project.poopkey.application.render.dto.FloorCongestion;
import com.project.poopkey.application.render.dto.RestroomRender;
import com.project.poopkey.application.render.service.FloorCongestionService;
import com.project.poopkey.application.render.service.RestroomRenderService;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.stereotype.Component;
import org.springframework.web.socket.CloseStatus;
import org.springframework.web.socket.TextMessage;
import org.springframework.web.socket.WebSocketSession;
import org.springframework.web.socket.handler.TextWebSocketHandler;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

@Component
@Slf4j
@ComponentScan(basePackages = "com.project.poopkey.application.render")
public class WebSocketRenderHandler extends TextWebSocketHandler {

    @Autowired
    private FloorCongestionService floorCongestionService;

    @Autowired
    private RestroomRenderService restroomRenderService;

    private final ObjectMapper objectMapper  = new ObjectMapper();

    List<WebSocketSession> sessions = new ArrayList<>();
    Map<WebSocketSession, RenderInfoKey> map = new HashMap<>();
    @Override
    public void afterConnectionEstablished(WebSocketSession session) throws Exception {
        System.out.println("connect");
        System.out.println("user 세션과 연결됨: "+session);
        sessions.add(session);
    }

    @Override
    protected void handleTextMessage(WebSocketSession session, TextMessage message) throws Exception {
        String payload = message.getPayload();
        System.out.println(payload+": 이게 바로 보낸 메시지.");
        // 오브젝트 매퍼
        JsonNode jsonNode = objectMapper.readTree(payload);
        int buildingId = jsonNode.get("buildingId").asInt();
        int restroomId = jsonNode.get("restroomId").asInt();
        System.out.println("buildingId는:"+buildingId);
        System.out.println("restroomId는:"+restroomId);
        map.put(session, new RenderInfoKey(buildingId, restroomId));
//        예시 :
//        {
//            "buildingId": 2,
//            "restroomId": 4
//        }
        List<FloorCongestion> list = floorCongestionService.findFloorCongestionList(buildingId);
        RestroomRender restroomRender = restroomRenderService.findRestroomRender(restroomId);
        TextMessage renderInfo1 = new TextMessage(objectMapper.writeValueAsString(list));
        TextMessage renderInfo2 = new TextMessage(objectMapper.writeValueAsString(restroomRender));
        for( WebSocketSession ws : sessions){
            ws.sendMessage(renderInfo1);
            ws.sendMessage(renderInfo2);
        }
    }

    // 어려움. 센서에서 클라이언트로 정보의 흐름이 이동할 때는
    // 클라이언트 단에서 입력받은 json 정보가 없는 것이기 때문에, 어떤 정보를 보내야 할 지 애매함.
    // session에 저장된 정보를 가져와서 쓰는 방법이 가장 이상적으로 보이지만,
    // 아 맞다 map 같은 자료구조에 그냥 저장하고 있다가 클라이언트단 정보가 바뀌면 그냥 바꿔주기만 하면 되지!!.
    // 조금 쉬고 구현해보자.
    public void sendMsgToClient() throws IOException {
        System.out.println("이거는 센서쪽 신호가 클라이언트 쪽으로 전달되는 현상");
        for( WebSocketSession ws : sessions){
            int buildingId = map.get(ws).getBuildingId();
            int restroomId = map.get(ws).getRestroomId();
            List<FloorCongestion> list = floorCongestionService.findFloorCongestionList(buildingId);
            RestroomRender restroomRender = restroomRenderService.findRestroomRender(restroomId);
            TextMessage renderInfo1 = new TextMessage(objectMapper.writeValueAsString(list));
            TextMessage renderInfo2 = new TextMessage(objectMapper.writeValueAsString(restroomRender));
            ws.sendMessage(renderInfo1);
            ws.sendMessage(renderInfo2);
        }
    }

    @Override
    public void afterConnectionClosed(WebSocketSession session, CloseStatus status) throws Exception {
        map.remove(session);
        sessions.remove(session);
        System.out.println("웹소켓 연결이 종료됨");
    }
}