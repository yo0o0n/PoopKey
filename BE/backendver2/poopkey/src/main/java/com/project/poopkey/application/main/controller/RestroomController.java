package com.project.poopkey.application.main.controller;

import com.project.poopkey.application.main.dto.Restroom;
import com.project.poopkey.application.main.dto.RestroomInfoInsert;
import com.project.poopkey.application.main.service.RestroomService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@CrossOrigin("*")
@RequestMapping("/api")
public class RestroomController {
    // 기능에 따라 2개 이상 service객체를 가져와야 될 수 있다.
    // 화장실을 청소하는 경우 다른 table에 대한 정보를 같이 update할 필요가 있다.

    // @restroomservice
    // @stallservice
    // @statisticservice
    // @itemservice
    @Autowired
    private RestroomService restroomService;

    @GetMapping("/user/restroom/select")
    public ResponseEntity<?> restroomUserFindList(@RequestParam("buildingId") int buildingId){
        List<Restroom> list = restroomService.findRestroomList(buildingId);
        if(list==null || list.size()==0)
            return new ResponseEntity<Void>(HttpStatus.NO_CONTENT);
        return new ResponseEntity<List<Restroom>>(list, HttpStatus.OK);
    }

    @GetMapping("/master/restroom/select")
    public ResponseEntity<?> restroomMasterFindList(@RequestParam("buildingId") int buildingId){
        List<Restroom> list = restroomService.findRestroomList(buildingId);
        if(list==null || list.size()==0)
            return new ResponseEntity<Void>(HttpStatus.NO_CONTENT);
        return new ResponseEntity<List<Restroom>>(list, HttpStatus.OK);
    }

    @PostMapping("/master/restroom/insert")
    public ResponseEntity<Void> restroomAdd(@RequestBody RestroomInfoInsert restroomInfoInsert){
        restroomService.addRestroom(restroomInfoInsert);
        return new ResponseEntity<Void>(HttpStatus.CREATED);
    }

}
