<template>
  <b-aspect aspect="16:9" class="profiler-pie">
    <div ref="chart" class="w-100 h-100" />
  </b-aspect>
</template>

<script lang="ts">
import { Component, Prop, Ref, Vue, Watch } from "vue-property-decorator";

import { Color, color, colors, create, Optional, useTheme } from "@amcharts/amcharts4/core";
import { LabelBullet, NavigationBar, TreeMap } from "@amcharts/amcharts4/charts";
import animatedTheme from "@amcharts/amcharts4/themes/animated";
import { CpuProfileResult } from "./types";
import { LinearGradient } from "@amcharts/amcharts4/.internal/core/rendering/fills/LinearGradient";
import { RadialGradient } from "@amcharts/amcharts4/.internal/core/rendering/fills/RadialGradient";
import { Pattern } from "@amcharts/amcharts4/.internal/core/rendering/fills/Pattern";

useTheme(animatedTheme);

interface ChartData {
  name: string;
  count?: number;
  children?: ChartData[];
}

function prepareData(data: CpuProfileResult): ChartData[] {
  const child: ChartData = {
    name: data.name
  };
  if (data.children.length > 0) {
    child["children"] = data.children.map(prepareData).flat();
  } else {
    child["count"] = data.delta;
  }

  const result: ChartData[] = [];
  result.push(child);
  return result;
}

@Component
export default class MultilevelTreeMap extends Vue {
  @Ref("chart")
  private readonly chart!: HTMLDivElement;

  @Prop()
  private readonly data!: CpuProfileResult;

  private amChart: TreeMap | undefined = undefined;

  mounted(): void {
    this.amChart = create(this.chart, TreeMap);
    this.amChart.hiddenState.properties.opacity = 1;
    this.amChart.hiddenState.properties.fillOpacity = 1;
    this.amChart.properties.opacity = 1;
    this.amChart.maxLevels = 1;
    this.amChart.dataFields.value = "count";
    this.amChart.dataFields.name = "name";
    this.amChart.dataFields.children = "children";
    this.amChart.homeText = "Timings";
    this.amChart.layoutAlgorithm = this.amChart.squarify;
    this.amChart.zoomable = true;

    this.amChart.navigationBar = new NavigationBar();

    this.addSeries("0");
    this.addSeries("1");
    this.addSeries("2");
    this.addSeries("3");
    this.addSeries("4");
    this.addSeries("5");

    this.amChart.data = prepareData(this.data);
    this.amChart.zoom({ start: 0, end: 0 });
  }

  private addSeries(name: string): void {
    if (this.amChart) {
      const seriesTemplate = this.amChart.seriesTemplates.create(name);
      seriesTemplate.strokeWidth = 2;
      seriesTemplate.columns.template.fillOpacity = 1;
      seriesTemplate.bulletsContainer.hiddenState.properties.opacity = 0;
      seriesTemplate.bulletsContainer.hiddenState.properties.visible = true;

      const bullet = seriesTemplate.bullets.push(new LabelBullet());
      bullet.locationX = 0.5;
      bullet.locationY = 0.5;
      bullet.label.text = "{name}";
      bullet.label.fill = color("#ffffff");

      const columnTemplate = seriesTemplate.columns.template;
      columnTemplate.column.cornerRadius(10, 10, 10, 10);
      const hoverState = columnTemplate.states.create("hover");

      hoverState.adapter.add("fill", (fill: Optional<Color | LinearGradient | RadialGradient | Pattern>) => {
        if (fill instanceof Color) {
          return color(colors.brighten(fill.rgb, -0.2));
        }
        return fill;
      });
    }
  }

  beforeDestroy(): void {
    if (this.amChart) {
      this.amChart.dispose();
    }
  }

  @Watch("data")
  private watchData(data: CpuProfileResult): void {
    if (this.amChart) {
      const result = prepareData(data);
      this.amChart.addData(result, 1);
      // this.amChart.data = result;
    }
  }
}
</script>
