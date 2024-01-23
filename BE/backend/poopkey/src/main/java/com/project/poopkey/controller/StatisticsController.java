package com.project.poopkey.controller;


import com.project.poopkey.model.dto.Statistics;
import com.project.poopkey.model.service.StatisticsService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api")
@CrossOrigin("*")
public class StatisticsController {
    // 외부 API로 제공하는 것과
    // 관리자가 직접 보는 화면과 총 2가지 메서드로 만들기

    @Autowired
    private StatisticsService statisticsService;
//    http://{SERVER_URL}/api/developer/openapi?buildingName={buildingName}&floor={floor}&gender={gender}
    @GetMapping("/developer/openapi")
    public ResponseEntity<?> statisticsAPIFind
    (@RequestParam("buildingName") String buildingName, @RequestParam("floor")int floor,
     @RequestParam("gender") int gender){
        Statistics statistics = statisticsService.findStatistics(buildingName, floor, gender);
        if(statistics==null)
            return new ResponseEntity<Void>(HttpStatus.NO_CONTENT);
        return new ResponseEntity<Statistics>(statistics, HttpStatus.OK);
    }
}
