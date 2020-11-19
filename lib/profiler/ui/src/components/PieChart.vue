<template>
  <b-aspect aspect="16:9" class="profiler-pie">
    <div ref="chart" class="w-100 h-100" />
  </b-aspect>
</template>

<script lang="ts">
import { Component, Prop, Ref, Vue, Watch } from "vue-property-decorator";

import { create, useTheme } from "@amcharts/amcharts4/core";
import { PieChart, PieSeries } from "@amcharts/amcharts4/charts";
import animatedTheme from "@amcharts/amcharts4/themes/animated";

useTheme(animatedTheme);

interface Marks {
  name: string;
  delta: string;
  index: number;
}

@Component
export default class HelloWorld extends Vue {
  @Ref("chart")
  private readonly chart!: HTMLDivElement;

  @Prop()
  private readonly data!: Marks[];

  private amChart: PieChart | undefined = undefined;

  mounted() {
    console.log(this.chart, this.data);

    this.amChart = create(this.chart, PieChart);
    this.amChart.data = this.data;
    const pieSeries = this.amChart.series.push(new PieSeries());
    pieSeries.dataFields.value = "delta";
    pieSeries.dataFields.category = "name";
  }

  beforeDestroy() {
    if (this.amChart) {
      this.amChart.dispose();
    }
  }

  @Watch("data")
  private watchData(data: Marks[]) {
    if (this.amChart) {
      this.amChart.data = data;
    }
  }
}
</script>
