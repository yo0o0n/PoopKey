package com.project.poopkey.application.main.controller;

import com.project.poopkey.application.main.dto.StallUpdate;
import com.project.poopkey.application.main.service.StallUpdateService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
@CrossOrigin("*")
@RequestMapping("/api")
public class StallUpdateController {
    @Autowired
    private StallUpdateService stallUpdateService;

    @PutMapping("/master/stalls/update")
    private ResponseEntity<?> stallUpdateModify(@RequestBody StallUpdate stallUpdate){
        stallUpdateService.modifyStallUpdate(stallUpdate);
        return new ResponseEntity<Void>(HttpStatus.OK);
    }
}
