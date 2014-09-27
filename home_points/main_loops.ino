
void switch_loop(int state) {
  switch(state) {
    case ROUTER_SETUP_STATE: router_setupLoop(); break;
    case ROUTER_WORK_STATE: router_workLoop(); break;
    case POINT_INIT_STATE: point_initLoop(); break;
  }
}

