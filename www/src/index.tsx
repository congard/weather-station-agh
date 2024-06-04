import React from "react";
import ReactDOM from "react-dom/client";
import App from "./component/App";

import {
  createTheme, ThemeProvider
} from '@mui/material/styles';
import CssBaseline from '@mui/material/CssBaseline';

const materialTheme = createTheme({
  palette: {
    mode: 'dark',
  },
});

const root = ReactDOM.createRoot(
  document.getElementById("root") as HTMLElement
);

root.render(
  <React.StrictMode>
    <ThemeProvider
      theme={materialTheme}
    >
      <CssBaseline enableColorScheme />
      <App />
    </ThemeProvider>
  </React.StrictMode>
);
