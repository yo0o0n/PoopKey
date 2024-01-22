package com.project.poopkey.controller;

import com.project.poopkey.model.dto.Report;
import com.project.poopkey.model.service.ReportService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

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
}
