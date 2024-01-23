package com.project.poopkey.controller;

import com.project.poopkey.model.dto.TissueShortageStatus;
import com.project.poopkey.model.service.TissueShortageStatusService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api")
@CrossOrigin("*")
public class TissueShortageStatusController {
    // 관리자와 사용자가 기능은 공통인 getmapping을 2개 만든다.
    @Autowired
    private TissueShortageStatusService tissueShortageStatusService;

    @GetMapping("/user/tissue-empty/{stallId}")
    public ResponseEntity<?> tissueShortageStatusUserFind(@PathVariable("stallId") long stallId){
        TissueShortageStatus tissueShortageStatus = tissueShortageStatusService.findTissueShortageStatus(stallId);
        if(tissueShortageStatus==null)
            return new ResponseEntity<Void>(HttpStatus.NO_CONTENT);
        return new ResponseEntity<TissueShortageStatus>(tissueShortageStatus, HttpStatus.OK);
    }

    @GetMapping("/master/tissue-empty/{stallId}")
    public ResponseEntity<?> tissueShortageStatusMasterFind(@PathVariable("stallId") long stallId){
        TissueShortageStatus tissueShortageStatus = tissueShortageStatusService.findTissueShortageStatus(stallId);
        if(tissueShortageStatus==null)
            return new ResponseEntity<Void>(HttpStatus.NO_CONTENT);
        return new ResponseEntity<TissueShortageStatus>(tissueShortageStatus, HttpStatus.OK);
    }

}
