import * as React from 'react';
import Stack from '@mui/material/Stack';
import Box from '@mui/material/Box';
import ToggleButtonGroup from '@mui/material/ToggleButtonGroup';
import ToggleButton from '@mui/material/ToggleButton';
import {BarChart, BarChartProps} from '@mui/x-charts/BarChart';
import {LineChart, LineChartProps} from '@mui/x-charts/LineChart';
import {HTRecord} from "../api/ht/HTRecord";
import {Observable} from "../core/Observable";
import {useEffect} from "react";
import {LocalConfig} from "../core/LocalConfig";

export type HTChartsProps = {
  config: LocalConfig,
  data: HTRecord[],
  dataSupplier: Observable<HTRecord[]>
}

type DatasetRecord = {
  humidity: number,
  temperature: number,
  date: string
}

export default function HTCharts({ config, data, dataSupplier }: HTChartsProps) {
  const [dataset, setDataset] = React.useState<DatasetRecord[]>([]);
  const [chartType, setChartType] = React.useState('line');

  const handleChartType = (event: any, newChartType: string) => {
    if (newChartType !== null) {
      setChartType(newChartType);
    }
  };

  const boxChartSettings: Partial<BarChartProps> = {
    dataset,
    height: 400,
    slotProps: {
      legend: {
        direction: 'row',
        position: { vertical: 'bottom', horizontal: 'middle' },
        padding: -5,
      },
    },
    xAxis: [{ scaleType: 'band', dataKey: 'date' }]
  };

  const lineChartSettings: Partial<LineChartProps> = {
    dataset,
    height: 400,
    slotProps: {
      legend: {
        direction: 'row',
        position: { vertical: 'bottom', horizontal: 'middle' },
        padding: -5,
      },
    },
    xAxis: [{ scaleType: 'band', dataKey: 'date' }]
  }

  console.log("HTCharts::render")

  useEffect(() => {
    console.log("HTCharts::ctor")

    const toDatasetRecord = (record: HTRecord): DatasetRecord => {
      return {
        humidity: record.humidity,
        temperature: record.temperature,
        date: record.timestamp.toLocaleString()
      };
    }

    let _dataset: DatasetRecord[] = data.map(record => toDatasetRecord(record));
    setDataset(_dataset);

    const recordListener = (records: HTRecord[]) => {
      const last = records[records.length - 1]

      if (_dataset.length >= config.maxRecordCount)
        _dataset = _dataset.slice(config.maxRecordCount - _dataset.length + 1)

      _dataset.push(toDatasetRecord(last));

      setDataset([..._dataset]);
    }

    dataSupplier.subscribe(recordListener)

    // unmounted
    return function() {
      dataSupplier.unsubscribe(recordListener)
      console.log("HTCharts::dtor")
    }
  }, []);

  return (
    <Stack
      direction={{ xs: 'column', xl: 'row' }}
      spacing={1}
      sx={{ width: '100%' }}
    >
      <Box sx={{ flexGrow: 1 }}>
        <div style={{paddingLeft:'35%', paddingRight:'35%', marginBottom: 32}}>
          <ToggleButtonGroup
            value={chartType}
            exclusive
            onChange={handleChartType}
            aria-label="chart type"
            fullWidth
          >
            {['line', 'bar'].map((type) => (
              <ToggleButton key={type} value={type} aria-label="left aligned">
                {type}
              </ToggleButton>
            ))}
          </ToggleButtonGroup>
        </div>

        {chartType === 'bar' && (
          <BarChart
            series={[
              { dataKey: 'humidity', label: 'Humidity', stack: 'A' },
              { dataKey: 'temperature', label: 'Temperature', stack: 'B' },
            ]}
            {...boxChartSettings}
          />
        )}

        {chartType === 'line' && (
          <LineChart
            series={[
              { dataKey: 'humidity', label: 'Humidity', stack: 'A' },
              { dataKey: 'temperature', label: 'Temperature', stack: 'B' },
            ]}
            {...lineChartSettings}
          />
        )}
      </Box>
    </Stack>
  );
}
