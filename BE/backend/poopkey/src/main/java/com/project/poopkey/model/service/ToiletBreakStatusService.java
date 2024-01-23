package com.project.poopkey.model.service;

import com.project.poopkey.model.dto.ToiletBreakStatus;

public interface ToiletBreakStatusService {
    ToiletBreakStatus findToiletBreakStatus(long stallId);
}
