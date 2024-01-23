package com.project.poopkey.controller;

import com.project.poopkey.model.dto.ToiletBreakStatus;
import com.project.poopkey.model.service.ToiletBreakStatusService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api")
@CrossOrigin("*")
public class ToiletBreakStatusController {
    // 관리자와 사용자가 기능은 공통인 getmapping을 2개 만든다.
    @Autowired
    private ToiletBreakStatusService toiletBreakStatusService;

    @GetMapping("/user/toilet-breakdown/{stallId}")
    public ResponseEntity<?> toiletBreakStatusUserFind(@PathVariable("stallId") long stallId){
        ToiletBreakStatus toiletBreakStatus = toiletBreakStatusService.findToiletBreakStatus(stallId);
        if(toiletBreakStatus==null)
            return new ResponseEntity<Void>(HttpStatus.NO_CONTENT);
        return new ResponseEntity<ToiletBreakStatus>(toiletBreakStatus, HttpStatus.OK);
    }

    @GetMapping("/master/toilet-breakdown/{stallId}")
    public ResponseEntity<?> toiletBreakStatusMasterFind(@PathVariable("stallId") long stallId){
        ToiletBreakStatus toiletBreakStatus = toiletBreakStatusService.findToiletBreakStatus(stallId);
        if(toiletBreakStatus==null)
            return new ResponseEntity<Void>(HttpStatus.NO_CONTENT);
        return new ResponseEntity<ToiletBreakStatus>(toiletBreakStatus, HttpStatus.OK);
    }
}
