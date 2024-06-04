import * as React from 'react';
import AppContent from "./AppContent";
import Box from "@mui/material/Box";
import AppHeader from "./AppHeader";
import {HTFetcher} from "../api/ht/HTFetcher";
import {HTService} from "../api/ht/HTService";
import {LocalConfig} from "../core/LocalConfig";

const config = new LocalConfig();

const htService = new HTService();
const htFetcher = new HTFetcher(htService, config);

htFetcher.start();

// TODO: show errors in snackbars
htFetcher.errorObservable.subscribe(error => console.log(error));

function App() {
  return (
    <Box style={{ height: "100vh" }}>
      <AppHeader />
      <AppContent config={config} htService={htService} htFetcher={htFetcher}/>
    </Box>
  );
}

export default App;
