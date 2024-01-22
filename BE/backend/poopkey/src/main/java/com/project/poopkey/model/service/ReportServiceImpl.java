package com.project.poopkey.model.service;


import com.project.poopkey.model.dao.ReportDao;
import com.project.poopkey.model.dto.Report;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class ReportServiceImpl implements ReportService{

    @Autowired
    private ReportDao reportDao;

    @Override
    public void addReport(Report report) {
        reportDao.insert(report);
    }
}
