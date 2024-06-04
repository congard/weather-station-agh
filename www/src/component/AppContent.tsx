import * as React from 'react';
import Tabs from '@mui/material/Tabs';
import Tab from '@mui/material/Tab';
import Typography from '@mui/material/Typography';
import Box from '@mui/material/Box';
import HTCharts from "./HTCharts";
import {LocalConfig} from "../core/LocalConfig";
import {HTService} from "../api/ht/HTService";
import {HTFetcher} from "../api/ht/HTFetcher";

interface TabPanelProps {
  children?: React.ReactNode;
  index: number;
  value: number;
}

function TabPanel(props: TabPanelProps) {
  const { children, value, index, ...other } = props;

  return (
    <div
      role="tabpanel"
      hidden={value !== index}
      id={`vertical-tabpanel-${index}`}
      aria-labelledby={`vertical-tab-${index}`}
      {...other}
    >
      {value === index && (
        <Box sx={{ p: 3 }}>
          <Typography>{children}</Typography>
        </Box>
      )}
    </div>
  );
}

function a11yProps(index: number) {
  return {
    id: `vertical-tab-${index}`,
    'aria-controls': `vertical-tabpanel-${index}`,
  };
}

type TabBoxProps = {
  children?: React.ReactNode;
}

function TabBox({ children }: TabBoxProps) {
  return (
    <Box style={{width: "50vw"}}>
      {children}
    </Box>
  );
}

export type TabsComponentProps = {
  config: LocalConfig;
  htService: HTService;
  htFetcher: HTFetcher;
}

export default function AppContent({ config, htService, htFetcher }: TabsComponentProps) {
  const [value, setValue] = React.useState(0);

  const handleChange = (event: React.SyntheticEvent, newValue: number) => {
    setValue(newValue);
  };

  return (
    <Box
      sx={{
        flexGrow: 1,
        bgcolor: 'background.paper',
        display: 'flex',
        padding: '32px',
        justifyContent: 'center'
      }}
    >
      <Tabs
        orientation="vertical"
        variant="scrollable"
        value={value}
        onChange={handleChange}
        aria-label="Vertical tabs example"
        sx={{
          borderRight: 1,
          borderColor: 'divider'
        }}
      >
        <Tab label="Charts" {...a11yProps(0)} />
        <Tab label="Historical" {...a11yProps(1)} />
        <Tab label="Settings" {...a11yProps(2)} />
        <Tab label="About" {...a11yProps(3)} />
      </Tabs>

      <TabPanel value={value} index={0}>
        <TabBox>
          <HTCharts
            config={config}
            data={htFetcher.fetchedRecords}
            dataSupplier={htFetcher.recordsObservable} />
        </TabBox>
      </TabPanel>

      <TabPanel value={value} index={1}>
        <TabBox>Historical data</TabBox>
      </TabPanel>

      <TabPanel value={value} index={2}>
        <TabBox>Settings</TabBox>
      </TabPanel>

      <TabPanel value={value} index={3}>
        <TabBox>About</TabBox>
      </TabPanel>
    </Box>
  );
}
