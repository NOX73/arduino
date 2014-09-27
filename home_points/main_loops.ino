
void setupMainLoops() {
  mainLoops[ROUTER_SETUP_STATE] = &router_setupLoop;
  mainLoops[ROUTER_WORK_STATE] = &router_workLoop;
  mainLoops[POINT_INIT_STATE] = &point_initLoop;
}

