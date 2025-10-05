"""
A simple program to test the vips_py module.
"""

import vips_py

vips_py.gamma_transform(
    "images/pexels-stijn-dijkstra-1306815-29988776.jpg", "images/test_out_095.jpg", 0.5
)
vips_py.gamma_transform(
    "images/pexels-stijn-dijkstra-1306815-29988776.jpg", "images/test_out_155.jpg", 1.55
)
