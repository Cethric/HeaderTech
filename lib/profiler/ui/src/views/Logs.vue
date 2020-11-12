<template>
  <b-container class="logs">
    <b-row>
      <b-form-group label="Visible Rows" label-for="row-selector">
        <b-select id="row-selector" v-model="visibleRows">
          <b-select-option :value="10">10</b-select-option>
          <b-select-option :value="20">20</b-select-option>
          <b-select-option :value="30">30</b-select-option>
          <b-select-option :value="40">40</b-select-option>
          <b-select-option :value="messages.length">All</b-select-option>
        </b-select>
      </b-form-group>
    </b-row>
    <b-row>
      <b-col>
        <b-table-simple hover small striped dark>
          <b-thead>
            <b-tr>
              <b-th>Time</b-th>
              <b-th>Thread</b-th>
              <b-th>Level</b-th>
              <b-th>Name</b-th>
              <b-th>Message</b-th>
            </b-tr>
          </b-thead>
          <b-tbody>
            <b-tr
              v-for="[id, msg] in messages.slice(messages.length - visibleRows)"
              :key="id"
            >
              <b-td>{{ formatTime(msg.time) }}</b-td>
              <b-td>{{ msg.thread }}</b-td>
              <b-td>{{ logName(msg.level) }}</b-td>
              <b-td>{{ msg.name }}</b-td>
              <b-td>{{ msg.data }}</b-td>
            </b-tr>
          </b-tbody>
        </b-table-simple>
      </b-col>
    </b-row>
  </b-container>
</template>

<style lang="scss" scoped>

</style>

<script lang="ts">
import { Component, Vue } from "vue-property-decorator";

interface LogMessage {
  name: string;
  data: string;
  time: number;
  thread: number;
  level: number;
}

@Component({})
export default class Logs extends Vue {
  private readonly logSource: EventSource = new EventSource(
    "http://localhost:8080/profiler/logs"
  );
  private messages: [string, LogMessage][] = [];
  private readonly logNames: string[] = [
    "Trace",
    "Debug",
    "Information",
    "Warning",
    "Error",
    "Critical"
  ];
  private visibleRows = 10;

  public mounted() {
    this.logSource.onmessage = ev => {
      this.pushMessage(ev.lastEventId, JSON.parse(ev.data));
    };
  }

  private logName(level: number) {
    return this.logNames[level];
  }

  private formatTime(time: string): string {
    const date = new Date(time);
    return `${date.getDay()}/${date.getMonth()}/${date.getFullYear()} ${date.getHours()}:${date.getMinutes()}:${date.getSeconds()}.${date.getMilliseconds()}`;
  }

  private pushMessage(id: string, message: LogMessage) {
    setTimeout(
      () => this.$nextTick(() => this.messages.push([id, message])),
      10
    );
    const MAX_LENGTH = 256;
    if (this.messages.length > MAX_LENGTH) {
      this.messages = this.messages.slice(this.messages.length - MAX_LENGTH);
    }
  }
}
</script>
