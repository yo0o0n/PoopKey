package com.project.poopkey.application.main.dao;

import com.project.poopkey.application.main.dto.Report;

import java.util.List;

public interface ReportDao {
    public void insert(Report report);

    public List<Report> selectList(int masterId);
}
