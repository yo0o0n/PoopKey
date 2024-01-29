package com.project.poopkey.application.main.controller;

import com.project.poopkey.application.main.service.MasterService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
@CrossOrigin("*")
@RequestMapping("/api")
public class MasterController {
    @Autowired
    private MasterService masterService;
    @PutMapping("/master/delete")
    public ResponseEntity<?> masterRemove(@RequestParam("email")String email){
        masterService.removeMaster(email);
        return new ResponseEntity<Void>(HttpStatus.OK);
    }
}
