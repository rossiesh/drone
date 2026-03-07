idf_component_register(
    SRCS "main.cpp"
    INCLUDE_DIRS "."
    REQUIRES driver
    PRIV_REQUIRES spi_flash
)