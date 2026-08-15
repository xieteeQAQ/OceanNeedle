#pragma once

enum class ImportMode
{
    STRICT,
    LENIENT
};

enum class DuplicatePolicy
{
    SKIP,
    UPDATE,
    ERROR
};

enum class ImportStatus
{
    SUCCESS,
    FAILED,
    SKIPPED
};