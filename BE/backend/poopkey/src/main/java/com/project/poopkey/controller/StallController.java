package com.project.poopkey.controller;

import com.project.poopkey.model.dto.Stall;
import com.project.poopkey.model.service.StallService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

// http://{SERVER_URL}/api/user/stalls/detail?stallId={stallId}
@RestController
@RequestMapping("/api")
@CrossOrigin("*")
public class StallController {
    @Autowired
    private StallService stallService;
    @GetMapping("/user/stalls/detail")
    public ResponseEntity<Stall> stallUserFind(@RequestParam("stallId") long stallId){
        Stall stall = stallService.findStall(stallId);
        return new ResponseEntity<Stall>(stall, HttpStatus.OK);
    }

    @GetMapping("/master/stalls/detail")
    public ResponseEntity<Stall> stallMasterFind(@RequestParam("stallId") long stallId){
        Stall stall = stallService.findStall(stallId);
        return new ResponseEntity<Stall>(stall, HttpStatus.OK);
    }
    @PutMapping("/master/stalls/update")
    public ResponseEntity<Void> stallModify(@RequestBody Stall stall){
        stallService.modifyStall(stall);
        return new ResponseEntity<Void>(HttpStatus.OK);
    }
}
