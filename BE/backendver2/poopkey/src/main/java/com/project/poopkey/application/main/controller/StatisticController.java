package com.project.poopkey.application.main.controller;

import com.project.poopkey.application.main.dto.Statistic;
import com.project.poopkey.application.main.service.StatisticService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
@CrossOrigin("*")
@RequestMapping("/api")
public class StatisticController {
    @Autowired
    private StatisticService statisticService;
    // http://{SERVER_URL/api/master/statistics?buildingName={buildingName}&floor={floor}&gender={gender}
    @GetMapping("/master/statistics")
    public ResponseEntity<?> statisticMasterFind(@RequestParam("buildingName")String buildingName, @RequestParam("floor")int floor, @RequestParam("gender")int gender){
        Statistic statistic = statisticService.findStatistic(buildingName, floor, gender);
        if(statistic==null)
            return new ResponseEntity<Void>(HttpStatus.NO_CONTENT);
        return new ResponseEntity<Statistic>(statistic, HttpStatus.OK);
    }
    // http://{SERVER_URL}/api/developer/openapi?buildingName={buildingName}&floor={floor}&gender={gender}
    @GetMapping("/developer/openapi")
    public ResponseEntity<?> statisticDeveloperFind(@RequestParam("buildingName")String buildingName, @RequestParam("floor")int floor, @RequestParam("gender")int gender){
        Statistic statistic = statisticService.findStatistic(buildingName, floor, gender);
        if(statistic==null)
            return new ResponseEntity<Void>(HttpStatus.NO_CONTENT);
        return new ResponseEntity<Statistic>(statistic, HttpStatus.OK);
    }
}
