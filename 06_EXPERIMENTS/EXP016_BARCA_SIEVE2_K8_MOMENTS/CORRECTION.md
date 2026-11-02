# EXP016 correction record

Before the first execution, a manually prepared placeholder raw file
mistakenly copied the (k=7) moment values (`2295/182`, `16797/104`, and
`165639/66248`) into the k=8 record. The script was then executed, the mistake
was detected by comparing the output, and `RAW_OUTPUT.txt` was replaced with
the actual k=8 output (`2565/182`, `4183559/20748`, and `1422011/472017`).
The incorrect placeholder was not an executed experiment result; this file
preserves the correction history so it is not silently obscured.
