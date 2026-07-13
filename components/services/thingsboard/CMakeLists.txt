idf_component_register(
    SRCS "src/tb_client.c" "src/tb_telemetry.c" "src/tb_attributes.c" "src/tb_rpc.c"
    INCLUDE_DIRS "include"
    REQUIRES mqtt 
)
