package com.project.poopkey.application.main.controller;

import com.project.poopkey.application.main.dto.StallDetail;
import com.project.poopkey.application.main.service.StallDetailService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
@CrossOrigin("*")
@RequestMapping("/api")
public class StallDetailController {
    @Autowired
    private StallDetailService stallDetailService;
    // http://{SERVER_URL}/api/master/stalls/detail?stallId={stallId}
    @GetMapping("/master/stalls/detail")
    public ResponseEntity<?> stallMasterDetailFind(@RequestParam("stallId")long stallId){
        StallDetail stallDetail = stallDetailService.findStallDetail(stallId);
        if(stallDetail==null)
            return new ResponseEntity<Void>(HttpStatus.NO_CONTENT);
        return new ResponseEntity<StallDetail>(stallDetail, HttpStatus.OK);
    }

    @GetMapping("/user/stalls/detail")
    public ResponseEntity<?> stallUserDetailFind(@RequestParam("stallId")long stallId){
        StallDetail stallDetail = stallDetailService.findStallDetail(stallId);
        if(stallDetail==null)
            return new ResponseEntity<Void>(HttpStatus.NO_CONTENT);
        return new ResponseEntity<StallDetail>(stallDetail, HttpStatus.OK);
    }
}
