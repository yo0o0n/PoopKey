package com.project.poopkey.application.main.service;

import com.project.poopkey.application.main.dto.Report;

import java.util.List;

public interface ReportService {
    void addReport(Report report);

    List<Report> findReportList(int masterId);
}
