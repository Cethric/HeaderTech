<template>
  <b-aspect aspect="16:9" class="profiler-pie">
    <div ref="chart" class="w-100 h-100" />
  </b-aspect>
</template>

<script lang="ts">
import { Component, Prop, Ref, Vue, Watch } from "vue-property-decorator";

import { ColorSet, create, percent, Scrollbar, useTheme } from "@amcharts/amcharts4/core";
import { CategoryAxis, ColumnSeries, DurationAxis, XYChart } from "@amcharts/amcharts4/charts";
import animatedTheme from "@amcharts/amcharts4/themes/animated";
import { CpuProfileResult } from "./types";

useTheme(animatedTheme);

interface ChartData {
  category: string;
  name: string;
  start: number;
  end: number;
  delta: number;
}

function prepareData(data: CpuProfileResult): ChartData[] {
  const result: ChartData[] = [
    {
      category: data.name,
      name: `${data.name}-${Math.random()}`,
      start: data.start,
      end: data.end,
      delta: data.delta
    }
  ];
  if (data.children) {
    result.push(...data.children.map(prepareData).flat());
  }
  return result;
}

@Component
export default class MultilevelTreeMap extends Vue {
  @Ref("chart")
  private readonly chart!: HTMLDivElement;

  @Prop()
  private readonly data!: CpuProfileResult;

  private amChart: XYChart | undefined = undefined;
  private interval?: number;

  mounted(): void {
    this.amChart = create(this.chart, XYChart);
    this.amChart.hiddenState.properties.opacity = 0; // this creates initial fade-in

    this.amChart.paddingRight = 30;

    const colorSet = new ColorSet();
    colorSet.saturation = 0.4;

    const categoryAxis = this.amChart.yAxes.push(new CategoryAxis());
    categoryAxis.dataFields.category = "category";
    categoryAxis.renderer.grid.template.location = 0;
    categoryAxis.renderer.inversed = true;

    const dateAxis = this.amChart.xAxes.push(new DurationAxis());
    categoryAxis.dataFields.data = "delta";
    dateAxis.renderer.minGridDistance = 70;
    dateAxis.baseUnit = "millisecond";
    dateAxis.renderer.tooltipLocation = 0;

    const series1 = this.amChart.series.push(new ColumnSeries());
    series1.columns.template.height = percent(70);
    series1.columns.template.tooltipText = "{category}: [bold]{delta}[/]";

    series1.dataFields.openValueX = "start";
    series1.dataFields.valueX = "end";
    series1.dataFields.categoryY = "category";
    series1.columns.template.propertyFields.fill = "color"; // get color from data
    series1.columns.template.propertyFields.stroke = "color";
    series1.columns.template.strokeOpacity = 1;

    this.amChart.scrollbarX = new Scrollbar();

    this.amChart.data = [this.data].map(prepareData).flat();

    this.interval = setInterval(() => this.amChart.removeData(20), 500);
  }

  beforeDestroy(): void {
    if (this.amChart) {
      this.amChart.dispose();
    }
    clearInterval(this.interval);
  }

  @Watch("data")
  private watchData(data: CpuProfileResult): void {
    if (this.amChart) {
      const result = [data].map(prepareData).flat();
      this.amChart.addData(result, 0);
      // this.amChart.data = result;
    }
  }
}
</script>
