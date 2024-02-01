package com.project.poopkey.application.main.controller;

import com.project.poopkey.application.main.dto.StallUpdate;
import com.project.poopkey.application.main.service.StallUpdateService;
import com.project.poopkey.clientsocket.WebSocketRenderHandler;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.io.IOException;

@RestController
@CrossOrigin("*")
@RequestMapping("/api")
public class StallUpdateController {
    @Autowired
    private StallUpdateService stallUpdateService;

    @Autowired
    private WebSocketRenderHandler webSocketRenderHandler;
    // 관리자가 칸 상태를 바꾸면 클라이언트에 웹소켓으로 실시간으로 랜더링 내용을 전달해야된다.
    @PutMapping("/master/stalls/update")
    private ResponseEntity<?> stallUpdateModify(@RequestBody StallUpdate stallUpdate) throws IOException {
        stallUpdateService.modifyStallUpdate(stallUpdate);
        webSocketRenderHandler.sendMsgToClient();
        return new ResponseEntity<Void>(HttpStatus.OK);
    }
}
