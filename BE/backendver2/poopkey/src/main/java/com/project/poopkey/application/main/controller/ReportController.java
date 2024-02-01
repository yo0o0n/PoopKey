package com.project.poopkey.application.main.controller;

import com.project.poopkey.application.main.dto.Report;
import com.project.poopkey.application.main.service.ReportService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@CrossOrigin("*")
@RequestMapping("/api")
public class ReportController {
    @Autowired
    private ReportService reportService;

    @PostMapping("/user/reports/regist")
    public ResponseEntity<Report> reportAdd(@RequestBody Report report){
        reportService.addReport(report);
        return new ResponseEntity<Report>(report, HttpStatus.CREATED);
    }
    /**스웨거에서 테스트 하고 이후 WebSocket파일로 옮긴다.*/
    @GetMapping("/master/reports/select")
    public ResponseEntity<?> reportListFind(@RequestParam("masterId") int masterId){
        List<Report> list = reportService.findReportList(masterId);
        if(list==null || list.size()==0)
            return new ResponseEntity<Void>(HttpStatus.NO_CONTENT);
        return new ResponseEntity<List<Report>>(list, HttpStatus.OK);
    }
}
