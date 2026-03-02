#pragma once

#define forEach(item, array, count) for (typeof(count) _i = 0; _i < (count) && ((item) = &(array)[_i], 1); _i++)

#define forEachIndexed(item, index, array, count) for (typeof(count) idx = 0; idx < (count) && ((item) = &(array)[idx], 1); idx++)

#define repeat(n, it) for (typeof(n) it = 0; it < (n); it++)