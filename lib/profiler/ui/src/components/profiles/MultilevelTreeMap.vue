<template>
  <b-aspect aspect="16:9" class="profiler-pie">
    <div ref="chart" class="w-100 h-100" />
  </b-aspect>
</template>

<script lang="ts">
import { Component, Prop, Ref, Vue, Watch } from "vue-property-decorator";

import { Color, color, colors, create, useTheme } from "@amcharts/amcharts4/core";
import { LabelBullet, NavigationBar, TreeMap } from "@amcharts/amcharts4/charts";
import animatedTheme from "@amcharts/amcharts4/themes/animated";
import { ProfileMark } from "./types";

useTheme(animatedTheme);

interface ChartData {
  name: string;
  count?: number;
  children?: ChartData[];
}

function prepareData(data: ProfileMark): ChartData[] {
  console.log(data);
  const child = {
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
  private readonly data!: ProfileMark;

  private amChart: TreeMap | undefined = undefined;

  mounted(): void {
    this.amChart = create(this.chart, TreeMap);
    this.amChart.hiddenState.properties.opacity = 0; // this makes initial fade in effect

    this.amChart.maxLevels = 2;
    this.amChart.dataFields.value = "count";
    this.amChart.dataFields.name = "name";
    this.amChart.dataFields.children = "children";
    this.amChart.homeText = "Timings";

    this.amChart.navigationBar = new NavigationBar();

    const level0SeriesTemplate = this.amChart.seriesTemplates.create("0");
    level0SeriesTemplate.strokeWidth = 2;

    level0SeriesTemplate.bulletsContainer.hiddenState.properties.opacity = 1;
    level0SeriesTemplate.bulletsContainer.hiddenState.properties.visible = true;

    const columnTemplate = level0SeriesTemplate.columns.template;
    const hoverState = columnTemplate.states.create("hover");

    hoverState.adapter.add("fill", function(fill, target) {
      if (fill instanceof Color) {
        return color(colors.brighten(fill.rgb, -0.2));
      }
      return fill;
    });

    this.addSeries("1");
    this.addSeries("2");
    this.addSeries("3");

    const data = prepareData(this.data);
    console.log(JSON.stringify(data));
    this.amChart.data = data;
  }

  private addSeries(name: string): void {
    const level1SeriesTemplate = this.amChart.seriesTemplates.create(name);
    level1SeriesTemplate.columns.template.fillOpacity = 0;

    const bullet1 = level1SeriesTemplate.bullets.push(new LabelBullet());
    bullet1.locationX = 0.5;
    bullet1.locationY = 0.5;
    bullet1.label.text = "{name}";
    bullet1.label.fill = color("#ffffff");
  }

  beforeDestroy(): void {
    if (this.amChart) {
      this.amChart.dispose();
    }
  }

  @Watch("data")
  private watchData(data: ProfileMark[]): void {
    if (this.amChart) {
      const result = prepareData(data);
      console.log(JSON.stringify(result));
      this.amChart.data = result;
    }
  }
}
</script>
